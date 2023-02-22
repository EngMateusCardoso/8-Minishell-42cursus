/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:23:59 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/22 18:59:21 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_builtin(char **cmds)
{
	int	exit_status;

	exit_status = 0;
	if (cmds[1])
	{
		exit_status = ft_atoi(cmds[1]);
		if (exit_status == 0 && (ft_strncmp(cmds[1], "0", 2) != 0))
		{
			error_msg("exit", ": numeric argument required", 2);
			exit_status = 2;
		}
		else if (cmds[2])
		{
			ft_putstr_fd("exit\n", 2);
			error_msg("exit", ": too many arguments", -1);
			return ;
		}
	}
	else
		exit_status = 0;
	finish_minishell();
	exit(exit_status);
}
