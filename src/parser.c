/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:30:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/24 20:29:43 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int  is_redirection_or_pipe(char *token)
{
    if (token == NULL)
        return (0);
    if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
        ft_strncmp(token, "|", 1) == 0 || ft_strncmp(token, ">>", 2) == 0 || \
        ft_strncmp(token, "<<", 2) == 0 || ft_strncmp(token, "||", 2) == 0)
        return (1);
    return (0);
}

char    **put_args(char **command_tokens, int index_table)
{
    char    **args;
    int     end_index;
    int     start_index;
    int     i;

    i = 0;
    start_index = 0;
    while (i < index_table)
    {
        while (!is_redirection_or_pipe(command_tokens[start_index]))
            start_index++;
        start_index++;
        i++;
    }
    end_index = start_index;
    while (command_tokens[end_index] && !is_redirection_or_pipe(command_tokens[end_index]))
        end_index++;
    args = (char **)malloc(sizeof(char *) * (end_index - start_index + 1));
    i = 0;
    while (start_index < end_index)
    {
        args[i++] = ft_strdup(command_tokens[start_index]);
        start_index++;
    }
    args[i] = NULL;
    return (args);
}

size_t  get_command_table_size(char   **command_tokens)
{
    size_t  size;
    int     i;

    size = 0;
    i = 0;
    while (command_tokens[i])
    {
        if (is_redirection_or_pipe(command_tokens[i]))
            size++;
        i++;
    }
    return (size + 1);
}

char    ***parser(char   **command_tokens)
{
    char    ***command_table;
    int     cmd_table_size;
    int     index_table;

    cmd_table_size = get_command_table_size(command_tokens);
    command_table = (char ***)malloc(sizeof(char **) * (cmd_table_size + 1));
    index_table = 0;
    while (index_table < cmd_table_size)
    {
        command_table[index_table] = put_args(command_tokens, index_table);
        index_table++;
    }
    command_table[index_table] = NULL;
    return (command_table);
}
