/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:28:02 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/24 19:57:58 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_msg(char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (status >= 0)
		g_data.exit_code = status;
}

void	eof_msg(char *redir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(redir, 2);
	ft_putstr_fd("')\n", 2);
}

void	clear_quotes_loop(char **cmds)
{
	int		i;
	char	*cmd;

	i = 0;
	while (cmds[i])
	{
		cmd = cmds[i];
		cmds[i] = clear_quotes(cmd);
		free(cmd);
		i++;
	}
}

char	*clear_quotes(char *var)
{
	char	*cmd;
	int		i;

	cmd = NULL;
	i = -1;
	while (var[++i])
	{
		if (var[i] == '\'')
			i += single_mark_case(&var[i], &cmd);
		else if (var[i] == '\"')
			i += double_mark_case(&var[i], &cmd);
		else
			cmd = ft_straddchar(cmd, var[i]);
		if (!var[i])
			break ;
	}
	return (cmd);
}

int	has_chr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}
