/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:17:37 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/21 20:31:47 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  table_size(char ***table)
{
    int  size;

    size = 0;
    while (table[size])
        size++;
    return (size);
}

char    ***expand_command_table(char ***command_table)
{
    char    ***expanded_command_table;
    int     i;
    int     j;

    expanded_command_table = (char ***)malloc(sizeof(char **) * (table_size(command_table) + 1));
    i = 0;
    while (command_table[i])
    {
        j = 0;
        while (command_table[i][j])
            j++;
        expanded_command_table[i] = (char **)malloc(sizeof(char *) * (j + 1));
        j = 0;
        while (command_table[i][j])
        {
            expanded_command_table[i][j] = ft_strdup(command_table[i][j]);
            j++;
        }
        expanded_command_table[i][j] = NULL;
        i++;
    }
    expanded_command_table[i] = NULL;
    return (expanded_command_table);
}