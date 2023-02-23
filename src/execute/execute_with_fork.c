/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:17:57 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/22 21:51:23 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_with_fork(t_cmd *command_table)
{
	int	i;

	i = -1;
	while (command_table[++i].cmd_and_args)
	{
		if (!find_hash_var(g_data.hash_table[hash_function("PATH") \
				% TABLE_SIZE], "PATH") && \
				!is_builtin(command_table[i].cmd_and_args[0]))
		{
			error_msg(command_table[i].cmd_and_args[0], \
				": No such file or directory", 127);
			continue ;
		}
		g_data.pipes_pids->pids[i] = fork();
		capture_child_signals(g_data.pipes_pids->pids[i]);
		if (g_data.pipes_pids->pids[i] == 0)
		{
			close_pipes_in_child(i);
			set_redirections(command_table[i].redirections_and_files, i);
			run_single_command(command_table[i].cmd_and_args);
		}
		else
			signal(SIGINT, handler_signal_parent);
	}
	finish_execute_with_fork();
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

void	run_single_command(char **cmd_and_args)
{
	if (cmd_and_args[0] && \
		is_builtin(cmd_and_args[0]))
	{
		run_builtin(cmd_and_args, 1);
		finish_free();
		exit(0);
	}
	else
		run_native_command(cmd_and_args);
}
