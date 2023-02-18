/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:17:57 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 10:50:31 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_with_fork(t_cmd *command_table)
{
	int	i;

	i = 0;
	while (command_table[i].cmd_and_args)
	{
		// sinais gerais
	// 		signal(SIGINT, ctrlc_fork);
	// signal(SIGQUIT, ctrlc_fork);
		g_data.pipes_pids->pids[i] = fork();
		if (g_data.pipes_pids->pids[i] == 0)
		{
			// sinais para o child
			close_pipes_in_child(i);
			set_redirections(command_table[i].redirections_and_files, i);
			if (is_builtin(command_table[i].cmd_and_args[0]))
				run_builtin(command_table[i].cmd_and_args, 1);
			else
				run_single_command(command_table[i].cmd_and_args);
		}
		i++;
	}
	close_pipes_in_parent();
	wait_all_pids();
	close(g_data.pipes_pids->pipes[0][1]);
	close(g_data.pipes_pids->pipes[g_data.pipes_pids->total_cmd][0]);
}

void	close_pipes_in_child(int i)
{
	int	j;

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

void	close_pipes_in_parent(void)
{
	int	i;

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

void	wait_all_pids(void)
{
	int	i;

	i = 0;
	while (i < g_data.pipes_pids->total_cmd)
	{
		waitpid(g_data.pipes_pids->pids[i], NULL, 0);
		i++;
	}
}
