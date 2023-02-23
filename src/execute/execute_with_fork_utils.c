/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_with_fork_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:43:24 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/22 21:44:04 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
