/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/14 11:08:12 by matcardo         ###   ########.fr       */
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

void    execute_command(char *command)
{
    char    **command_tokens;
    char    ***command_table;

    // add_history(command);
    command_tokens = lexer(command);
    free(command);
    print_command_tokens(command_tokens);
    command_table = parser(command_tokens);
    free_command_tokens(command_tokens);
    // print_command_table(command_table);
    // free_command_tokens(command_tokens);
    if (is_builtin(command_table[0][0]))
        execute_builtin(command_table);
    free_command_table(command_table);
    // else
    //     execute_executable(command_tokens);
}

void    start_minishell(void)
{
    char    *prompt;
    char    *prompt_input;

    while (1)
    {
        prompt = get_prompt();
        prompt_input = readline(prompt);
        free(prompt);
        execute_command(prompt_input);
    }
}
