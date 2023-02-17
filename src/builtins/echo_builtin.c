/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:39:37 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/17 18:32:39 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_builtin(char **cmds)
{
	if (ft_strncmp(cmds[1], "-n", 3) == 0)
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
	char	*cmd;

	i = 2;
	while (cmds[i])
	{
		cmd = clear_quotes(cmds[i]);
		ft_putstr_fd(cmd, 1);
		ft_free_pointer((void *)&cmd);
		if (cmds[++i])
			ft_putchar_fd(' ', 1);
	}
}

void	print_echo(char **cmds)
{
	int		i;
	char	*cmd;

	i = 1;
	while (cmds[i])
	{
		cmd = clear_quotes(cmds[i]);
		ft_putstr_fd(cmd, 1);
		ft_free_pointer((void *)&cmd);
		if (cmds[++i])
			ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
}
