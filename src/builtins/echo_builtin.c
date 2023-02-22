/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:39:37 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/22 18:59:01 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo_builtin(char **cmds)
{
	if (ft_strncmp(cmds[1], "-nnnnnnnnnnnn", ft_strlen(cmds[1])) == 0)
		print_echo_n(cmds);
	else
	{
		print_echo(cmds);
	}
	g_data.exit_code = 0;
}

void	print_echo_n(char **cmds)
{
	int		i;
	int		flag;

	i = 2;
	flag = 0;
	while (cmds[i])
	{
		if (flag || ft_strncmp(cmds[i], "-nnnnnnnnn", ft_strlen(cmds[i])) != 0)
		{
			flag = 1;
			ft_putstr_fd(cmds[i], 1);
			if (cmds[i + 1])
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
}

void	print_echo(char **cmds)
{
	int		i;

	i = 1;
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], 1);
		if (cmds[++i])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
}
