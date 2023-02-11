/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:44:35 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/10 00:00:53 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    free_command_tokens(char **command_tokens)
{
    int i;

    i = 0;
    while (command_tokens[i])
    {
        free(command_tokens[i]);
        i++;
    }
    free(command_tokens[i]);
    free(command_tokens);
}

void    free_command_table(t_cmd *command_table)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
    {
        while (command_table[i].cmd_and_args[j])
        {
            free(command_table[i].cmd_and_args[j]);
            j++;
        }
        free(command_table[i].cmd_and_args[j]);
        j = 0;
        while (command_table[i].redirections_and_files[j])
        {
            free(command_table[i].redirections_and_files[j]);
            j++;
        }
        free(command_table[i].redirections_and_files[j]);
    free(command_table[i].cmd_and_args);
    free(command_table[i].redirections_and_files);
        j = 0;
        i++;
    }
    free(command_table[i].cmd_and_args);
    free(command_table[i].redirections_and_files);
    free(command_table);
}

void    free_pipes_and_pids(void)
{
    int i;

    i = 0;
    while (g_data.pipes_pids->pipes[i])
    {
        free(g_data.pipes_pids->pipes[i]);
        i++;
    }
    free(g_data.pipes_pids->pipes[i]);
    free(g_data.pipes_pids->pipes);
    free(g_data.pipes_pids->pids);
    free(g_data.pipes_pids);
}
