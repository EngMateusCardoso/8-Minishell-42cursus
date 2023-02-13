/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/13 17:21:36 by matcardo         ###   ########.fr       */
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


void    execute_with_fork(t_cmd *command_table)
{
    int i;

    i = 0;
    while (command_table[i].cmd_and_args)
    {
        g_data.pipes_pids->pids[i] = fork();
        if (g_data.pipes_pids->pids[i] == 0)
        {
            close_pipes_in_child(i);
		    if (i != 0)
				dup2(g_data.pipes_pids->pipes[i][0], STDIN_FILENO);
		    if (i != (g_data.pipes_pids->total_cmd - 1))
				dup2(g_data.pipes_pids->pipes[i + 1][1], STDOUT_FILENO);
            close(g_data.pipes_pids->pipes[i][0]);
            close(g_data.pipes_pids->pipes[i + 1][1]);
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
    execute_builtin(command_table->cmd_and_args);
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

void    execute_line(char *command)
{
    char    **command_tokens;
    t_cmd   *command_table;

    command_tokens = lexer(command);
    free(command);
    //print_command_tokens(command_tokens);
    if (check_syntax(command_tokens))
    {
        init_pipes_and_pids(count_pipes(command_tokens));
        command_table = parser(command_tokens);
        free_command_tokens(command_tokens);
        //print_command_table(command_table);
        g_data.command_table_expanded = expand_command_table(command_table);
        free_command_table(command_table);
        //print_command_table(g_data.command_table_expanded);

        // executar -------------
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
