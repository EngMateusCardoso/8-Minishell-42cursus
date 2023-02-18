/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:23:59 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 05:16:20 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_builtin(char **cmds)
{
	int	exit_status;

	exit_status = 0;
	if (cmds[1])
		exit_status = ft_atoi(cmds[1]);
	else
		exit_status = 0;
	finish_minishell();
	exit(exit_status);
}
