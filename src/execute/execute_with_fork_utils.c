/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:43:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/23 12:09:56 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_command(char **cmd_and_args)
{
	char	*cmd_path;
	char	*path;

	path = find_hash_var(g_data.hash_table[hash_function("PATH") \
				% TABLE_SIZE], "PATH");
	if (!path && !is_builtin(cmd_and_args[0]))
	{
		error_msg(cmd_and_args[0], ": No such file or directory", 127);
		return (0);
	}
	cmd_path = get_command_path(cmd_and_args[0]);
	if (!cmd_path)
	{
		if (has_chr(cmd_and_args[0], '/'))
			error_msg(cmd_and_args[0], ": No such file or directory", 127);
		else
			error_msg(cmd_and_args[0], ": command not found", 127);
		free(cmd_path);
		return (0);
	}
	free(cmd_path);
	return (1);
}

void	finish_execute_with_fork(void)
{
	close_pipes_in_parent();
	wait_all_pids();
	close(g_data.pipes_pids->pipes[0][1]);
	close(g_data.pipes_pids->pipes[g_data.pipes_pids->total_cmd][0]);
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
