/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:17:37 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/03 17:10:53 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

int     count_commands(t_cmd *command_table)
{
    int i;

    i = 0;
    while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
        i++;
    return (i);
}

t_cmd   *expand_command_table(t_cmd *command_table)
{
    t_cmd   *new_command_table;
    int     i;
    int     j;

    i = 0;
    j = 0;
    new_command_table = (t_cmd *)malloc(sizeof(t_cmd) * (count_commands(command_table) + 1));
    while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
    {
        new_command_table[i].cmd_and_args = (char **)malloc(sizeof(char *) * (count_args(command_table[i].cmd_and_args) + 1));
        while (command_table[i].cmd_and_args[j])
        {
            new_command_table[i].cmd_and_args[j] = ft_strdup(command_table[i].cmd_and_args[j]);
            j++;
        }
        new_command_table[i].cmd_and_args[j] = NULL;
        j = 0;
        new_command_table[i].redirections_and_files = (char **)malloc(sizeof(char *) * (count_args(command_table[i].redirections_and_files) + 1));
        while (command_table[i].redirections_and_files[j])
        {
            new_command_table[i].redirections_and_files[j] = ft_strdup(command_table[i].redirections_and_files[j]);
            j++;
        }
        new_command_table[i].redirections_and_files[j] = NULL;
        j = 0;
        i++;
    }
    new_command_table[i].cmd_and_args = NULL;
    new_command_table[i].redirections_and_files = NULL;
    return (new_command_table);
}