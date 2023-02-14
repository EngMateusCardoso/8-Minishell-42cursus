/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/14 15:50:40 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    close_pipes_in_child(int i)
{
    int j;

    j = 0;
    while (j <= g_data.pipes_pids->total_cmd)
    {
        if (j != i)
            close(g_data.pipes_pids->pipes[j][0]);
        if (j != i + 1)
            close(g_data.pipes_pids->pipes[j][1]);
        j++;
    }
}

void    close_pipes_in_parent(void)
{
    int i;

    i = 0;
    while (i <= g_data.pipes_pids->total_cmd)
    {
        if (i != 0)
            close(g_data.pipes_pids->pipes[i][1]);
        if (i != g_data.pipes_pids->total_cmd)
            close(g_data.pipes_pids->pipes[i][0]);
        i++;
    }
}

void    wait_all_pids(void)
{
    int i;

    i = 0;
    while (i < g_data.pipes_pids->total_cmd)
    {
        waitpid(g_data.pipes_pids->pids[i], NULL, 0);
        i++;
    }
}

char    *file_absolute_path(char *file)
{
    char *tmp;
    char *tmp2;
    char *tmp3;

    if (file[0] == '~')
    {
        tmp = ft_strjoin(getenv("HOME"), file + 1);
        tmp2 = ft_strjoin(tmp, "/");
        tmp3 = ft_strjoin(tmp2, file);
        free(tmp);
        free(tmp2);
        return (tmp3);
    }
    return (file);
}

int     open_file(char *file, int flags)
{
    int fd;

    fd = open(file, flags, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("'No such file or directory\n", 2);
    }
    return (fd);
}

int     open_fd_heredoc(char *file, int n_cmd)
{
    char    *temp;
    int     fd;

    temp = ft_itoa(n_cmd);    
    file = ft_strjoin("/tmp/inputfile", temp);
    free(temp);
    fd = open(file, O_RDONLY, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd("'No such file or directory\n", 2);
    }
    free(file);
    return (fd);
}

int has_input_redirection(char **redir_and_files)
{
    int i;

    i = 0;
    while (redir_and_files[i])
    {
        if (redir_and_files[i][0] == '<')
            return (1);
        i++;
    }
    return (0);
}

int has_output_redirection(char **redir_and_files)
{
    int i;

    i = 0;
    while (redir_and_files[i])
    {
        if (redir_and_files[i][0] == '>')
            return (1);
        i++;
    }
    return (0);
}

void    set_input_and_output(char **redir_and_files, int i)
{
    int     j;
    char    *file;
    int     fd[2];

    j = 0;
    while (redir_and_files[j])
    {
        file = redir_and_files[j + 1];
        if (redir_and_files[j][0] == '>')
        {
            if (redir_and_files[j][1] == '>')
                fd[1] = open_file(file, O_WRONLY | O_CREAT | O_APPEND);
            else
                fd[1] = open_file(file, O_WRONLY | O_CREAT | O_TRUNC);
            g_data.pipes_pids->pipes[i + 1][1] = fd[1];
        }
        else if (redir_and_files[j][0] == '<')
        {
            if (redir_and_files[j][1] == '<')
                fd[0] = open_fd_heredoc(file, i);
            else
                fd[0] = open_file(file, O_RDONLY);
            g_data.pipes_pids->pipes[i][0] = fd[0];
        }
        j++;
    }
	if (i != 0 || has_input_redirection(redir_and_files))
    	dup2(g_data.pipes_pids->pipes[i][0], STDIN_FILENO);
    if (i != (g_data.pipes_pids->total_cmd - 1) || has_output_redirection(redir_and_files))
    	dup2(g_data.pipes_pids->pipes[i + 1][1], STDOUT_FILENO);
    close(g_data.pipes_pids->pipes[i][0]);
    close(g_data.pipes_pids->pipes[i + 1][1]);
}

void    execute_with_fork(t_cmd *command_table)
{
    int i;

    i = 0;
    while (command_table[i].cmd_and_args)
    {
        // sinais gerais
        g_data.pipes_pids->pids[i] = fork();
        if (g_data.pipes_pids->pids[i] == 0)
        {
            // sinais para o child
            close_pipes_in_child(i);
            set_input_and_output(command_table[i].redirections_and_files, i);
            run_single_command(command_table[i].cmd_and_args);
        }
        i++;
    }
    close_pipes_in_parent();
    wait_all_pids();
    close(g_data.pipes_pids->pipes[0][1]);
    close(g_data.pipes_pids->pipes[g_data.pipes_pids->total_cmd][0]);
}

void        execute_no_fork(t_cmd *command_table)
{
    execute_builtin(command_table->cmd_and_args, 0);
}

short int   is_forked(t_cmd *command_table)
{

    if (command_table[0].cmd_and_args && \
        !(command_table[1].cmd_and_args) && \
        !(command_table[1].redirections_and_files) && \
        command_table[0].cmd_and_args && \
        command_table[0].cmd_and_args[0] && \
        (ft_strncmp(command_table[0].cmd_and_args[0], "exit", 4) == 0 || \
        ft_strncmp(command_table[0].cmd_and_args[0], "cd", 2) == 0 || \
        ft_strncmp(command_table[0].cmd_and_args[0], "export", 6) == 0 || \
        ft_strncmp(command_table[0].cmd_and_args[0], "unset", 5) == 0))
        return (0);
    return (1);
}

int     count_pipes(char **command_tokens)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (command_tokens[i])
    {
        if (ft_strncmp(command_tokens[i], "|", 1) == 0)
            count++;
        i++;
    }
    return (count);
}

void    init_pipes_and_pids(int n_pipes)
{
    int i;

    g_data.pipes_pids = malloc(sizeof(t_pipes_pids));
    g_data.pipes_pids->pipes = malloc(sizeof(int *) * (n_pipes + 3));
    g_data.pipes_pids->pids = malloc(sizeof(pid_t) * (n_pipes + 1));
    g_data.pipes_pids->total_cmd = n_pipes + 1;
    i = 0;
    while (i <= n_pipes + 1)
    {
        g_data.pipes_pids->pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(g_data.pipes_pids->pipes[i]) == -1)
            ft_putstr_fd("Error creating pipe\n", 2);
        if (i != n_pipes + 1)
            g_data.pipes_pids->pids[i] = 0;
        i++;
    }
    g_data.pipes_pids->pipes[i] = NULL;
    g_data.pipes_pids->total_cmd = n_pipes + 1;
}

char	*get_str_prompt(void)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(getenv("USER"), "@minishell:");
	prompt = ft_strjoin("\001\033[1;92m\002", tmp);
	free(tmp);
	return (prompt);
}

char	*get_str_path(void)
{
	char	*path;
	char	*home;
	char	*tmp;
	char	*tmp2;

	path = getcwd(NULL, 0);
	home = ft_strdup(getenv("HOME"));
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", &path[ft_strlen(home)]);
		tmp2 = ft_strjoin("\001\033[1;34m\002", tmp);
		free(path);
		free(home);
		free(tmp);
		return (tmp2);
	}
	else
	{
		tmp = ft_strjoin("\001\033[1;34m\002", path);
		free(path);
		free(home);
		return (tmp);
	}
}

char    *get_prompt(void)
{
    char    *prompt;
    char    *path;
    char    *tmp;
    char    *tmp2;

    prompt = get_str_prompt();
    path = get_str_path();
    tmp = ft_strjoin(prompt, path);
    tmp2 = ft_strjoin(tmp, "\001\033[0m\002$ ");
    free(path);
    free(prompt);
    free(tmp);
    return (tmp2);
}

void    open_heredoc(char *stop_str, int n_cmd)
{
    char    *line;
    int     fd;
    char    *file;
    char    *temp;

    temp = ft_itoa(n_cmd);    
    file = ft_strjoin("/tmp/inputfile", temp);
    free(temp);
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        write(2, "Error opening file\n", 19);
    while (1)
    {
        line = readline("> ");
        if (ft_strncmp(line, stop_str, ft_strlen(stop_str)) == 0)
        {
            free(line);
            break ;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    g_data.exit_code = 0;
    exit(0);
    // free child process?
}

// void	ctrlc_parent_hd(int signal)
// {
// 	(void)signal;
// 	if (signal == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		g_data.exit_code = 130;
// 		// g_data->not_run = 1;
// 	}
// }

void	init_heredoc(char *stop_str, int n_cmd)
{
	pid_t	pid;
	int	    wstatus;

	pid = fork();
	if (pid < 0)
		write(2, "Error forking\n", 14);
	// if (pid > 0)
	// 	signal(SIGINT, ctrlc_parent_hd);
	if (pid == 0)
		open_heredoc(stop_str, n_cmd);
	waitpid(-1, &wstatus, 0);
	g_data.exit_code = WEXITSTATUS(wstatus);
}

void    heredoc(t_cmd *command_table)
{
    int i;
    int j;

    i = 0;
    while (command_table[i].redirections_and_files)
    {
        j = 0;
        while (command_table[i].redirections_and_files[j])
        {
            if (ft_strncmp(command_table[i].redirections_and_files[j], "<<", 2) == 0)
            {
                init_heredoc(command_table[i].redirections_and_files[j + 1], i);
            }
            j++;
        }        
        i++;
    }
}

void    execute_line(char *command)
{
    char    **command_tokens;
    t_cmd   *command_table;

    command_tokens = lexer(command);
    free(command);
    if (check_syntax(command_tokens))
    {
        init_pipes_and_pids(count_pipes(command_tokens));
        command_table = parser(command_tokens);
        free_command_tokens(command_tokens);
        g_data.command_table_expanded = expand_command_table(command_table);
        free_command_table(command_table);
        heredoc(g_data.command_table_expanded);
        if (is_forked(g_data.command_table_expanded))
            execute_with_fork(g_data.command_table_expanded);
        else
            execute_no_fork(g_data.command_table_expanded);
        free_command_table(g_data.command_table_expanded);
        free_pipes_and_pids();
    }
}

void    start_minishell(void)
{
    char                *prompt;
    char                *prompt_input;
    struct sigaction	sint;
    struct sigaction	squit;

    while (1)
    {
        capture_signals(&sint, &squit);
        prompt = get_prompt();
        prompt_input = readline(prompt);
        free(prompt);
        if (prompt_input && *prompt_input)
		    add_history(prompt_input);
        execute_line(prompt_input);
    }
}
