/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:28:02 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/20 09:01:49 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_msg(char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_data.exit_code = status;
}

char	*clear_quotes(char *var)
{
	char	*cmd;
	int		i;

	cmd = NULL;
	i = 0;
	while (var[i])
	{
		if ((var[i] != '\'') && (var[i] != '\"'))
		{
			cmd = ft_straddchar(cmd, var[i]);
		}
		i++;
	}
	return (cmd);
}
