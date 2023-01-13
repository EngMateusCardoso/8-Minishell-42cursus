/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:30:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/13 16:28:48 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        while (ft_strncmp(command_tokens[start_index], "|", 1) != 0)
            start_index++;
        start_index++;
        i++;
    }
    end_index = start_index;
    while (command_tokens[end_index] && ft_strncmp(command_tokens[end_index], "|", 1) != 0)
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
        if (ft_strncmp(command_tokens[i], "|", 1) == 0)
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
