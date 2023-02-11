/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/11 13:37:45 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_with_fork(t_cmd *command_table)
{
    ft_putstr_fd("Executing with fork", 1);
    ft_putstr_fd(command_table[0].cmd_and_args[0], 1);
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
    g_data.pipes_pids->pipes = malloc(sizeof(int *) * (n_pipes + 2));
    g_data.pipes_pids->pids = malloc(sizeof(pid_t) * (n_pipes + 1));
    g_data.pipes_pids->total_cmd = n_pipes + 1;
    i = 0;
    while (i <= n_pipes)
    {
        g_data.pipes_pids->pipes[i] = malloc(sizeof(int) * 2);
        if (pipe(g_data.pipes_pids->pipes[i]) == -1)
            ft_putstr_fd("Error creating pipe", 2);
        i++;
    }
    // Não entendi pq tive que comentar isso para não ter leaks
    // g_data.pipes_pids->pipes[i] = malloc(sizeof(int) * 2);
    g_data.pipes_pids->pipes[i] = NULL;
    g_data.pipes_pids->total_cmd = n_pipes + 1;
}

char    *get_prompt(void)
{
    char    *prompt;
    char    *path;
    char    *tmp;
    char    *temp2;

    tmp = ft_strjoin(getenv("USER"), ":");
    path = getcwd(NULL, 0);
    prompt = ft_strjoin(tmp, path);
    temp2 = prompt;
    prompt = ft_strjoin(prompt, "$ ");
    free(tmp);
    free(temp2);
    free(path);
    return (prompt);
}

void    execute_line(char *command)
{
    char    **command_tokens;
    t_cmd   *command_table;

    // add_history(command);
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
        // print_command_table(g_data.command_table_expanded);

        // executar -------------
        if (is_forked(g_data.command_table_expanded))
            execute_with_fork(g_data.command_table_expanded);
        else
            execute_no_fork(g_data.command_table_expanded);
        // if (is_builtin(g_data.command_table_expanded[0].cmd_and_args[0]))
        //     execute_builtin(g_data.command_table_expanded[0].cmd_and_args);
        // else
        //     execute_executable(command_tokens);
        // executar -------------

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
        execute_line(prompt_input);
    }
}
