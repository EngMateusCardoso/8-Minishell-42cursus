/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:17:37 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/26 16:05:30 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*expand_command_table(t_cmd *cmd)
{
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd) * (count_commands(cmd) + 1));
	while (cmd[i].cmd_and_args || \
		cmd[i].redirections_and_files)
	{
		new_cmd[i].cmd_and_args = (char **)malloc(sizeof(char *) * \
			(count_args(cmd[i].cmd_and_args) + 1));
		expand_cmd_and_args(new_cmd[i].cmd_and_args, cmd[i].cmd_and_args);
		new_cmd[i].redirections_and_files = (char **)malloc(sizeof(char *) * \
			(count_args(cmd[i].redirections_and_files) + 1));
		expand_redirections_and_files(new_cmd[i].redirections_and_files, \
			cmd[i].redirections_and_files);
		i++;
	}
	new_cmd[i].cmd_and_args = NULL;
	new_cmd[i].redirections_and_files = NULL;
	return (new_cmd);
}

void	expand_cmd_and_args(char **new_cmds, char **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i])
	{
		if (can_expand(cmds[i]))
			expand_token(new_cmds, cmds[i], &j, cmds[0]);
		else
		{
			new_cmds[j] = ft_strdup(cmds[i]);
			j++;
		}
		i++;
	}
	new_cmds[j] = NULL;
	return ;
}

void	expand_redirections_and_files(char **new_redir, char **redir)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (redir[i])
	{
		if (can_expand(redir[i]))
			expand_token(new_redir, redir[i], &j, redir[0]);
		else
		{
			new_redir[j] = ft_strdup(redir[i]);
			j++;
		}
		i++;
	}
	new_redir[j] = NULL;
	return ;
}

void	expand_token(char **new_token, char *token, int *j, char *cmd)
{
	char	*expanded;

	expanded = NULL;
	if (has_wildcard(token) && ft_strncmp(cmd, "export", 6))
		expand_wildcard(new_token, token, j);
	else
	{
		expanded = expand_tilde(token);
		if (expanded == NULL)
			expanded = expand_money_sign(token);
		if (expanded != NULL)
		{
			new_token[*j] = expanded;
			*j += 1;
		}
	}
}
