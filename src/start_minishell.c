/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/12 00:46:42 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    command_tokens = lexer(command);
    free(command);
    //print_command_tokens(command_tokens);
    if (check_syntax(command_tokens))
    {
        command_table = parser(command_tokens);
        free_command_tokens(command_tokens);
        //print_command_table(command_table);
        g_data.command_table_expanded = expand_command_table(command_table);
        free_command_table(command_table);
        print_command_table(g_data.command_table_expanded);

        // executar -------------
        if (is_builtin(g_data.command_table_expanded[0].cmd_and_args[0]))
            execute_builtin(g_data.command_table_expanded[0].cmd_and_args);
        // else
        //     execute_executable(command_tokens);
        // executar -------------

        free_command_table(g_data.command_table_expanded);
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
