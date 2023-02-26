/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:39:37 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/25 21:01:50 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	echo_builtin(char **cmds)
{
	if (cmds[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if (ft_strncmp(cmds[1], "-nnnnnnnnnnnn", ft_strlen(cmds[1])) == 0)
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
	char	*cmd;

	i = 2;
	flag = 0;
	while (cmds[i])
	{
		cmd = clear_quotes(cmds[i]);
		if (cmd && (flag || ft_strncmp(cmd, "-nnnnnnnnn", ft_strlen(cmd)) != 0))
		{
			flag = 1;
			ft_putstr_fd(cmd, 1);
			if (cmds[i + 1])
				ft_putchar_fd(' ', 1);
		}
		ft_free_pointer((void *)&cmd);
		i++;
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
		if (cmds[++i])
			ft_putchar_fd(' ', 1);
		ft_free_pointer((void *)&cmd);
	}
	ft_free_pointer((void *)&cmd);
	ft_putchar_fd('\n', 1);
}
