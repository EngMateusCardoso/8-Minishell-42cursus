/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:30:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 00:14:25 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parser(char **command_tokens)
{
	t_cmd			*command_table;
	unsigned int	cmd_table_size;
	unsigned int	index_table;

	cmd_table_size = get_command_table_size(command_tokens);
	command_table = (t_cmd *)malloc(sizeof(t_cmd) * (cmd_table_size + 1));
	index_table = 0;
	while (index_table < cmd_table_size)
	{
		command_table[index_table] = put_complete_cmd(command_tokens, \
			index_table);
		index_table++;
	}
	command_table[index_table].cmd_and_args = NULL;
	command_table[index_table].redirections_and_files = NULL;
	return (command_table);
}

size_t	get_command_table_size(char **command_tokens)
{
	size_t			size;
	unsigned int	i;

	size = 0;
	i = 0;
	while (command_tokens[i])
	{
		if (ft_strncmp(command_tokens[i], "|", 1) == 0)
			size++;
		i++;
	}
	return (size + 1);
}

t_cmd	put_complete_cmd(char **command_tokens, unsigned int index_table)
{
	t_cmd			complete_cmd;
	unsigned int	end_index;
	unsigned int	start_index;
	unsigned int	i;

	i = 0;
	start_index = 0;
	while (i < index_table)
	{
		if (ft_strncmp(command_tokens[start_index], "|", 1) == 0)
			i++;
		start_index++;
	}
	end_index = start_index;
	while (command_tokens[end_index] && \
		ft_strncmp(command_tokens[end_index], "|", 1) != 0)
		end_index++;
	i = 0;
	complete_cmd.cmd_and_args = put_cmd_and_args(command_tokens, start_index, \
		end_index);
	complete_cmd.redirections_and_files = put_redirections(command_tokens, \
		start_index, end_index);
	return (complete_cmd);
}

char	**put_cmd_and_args(char **command_tokens, unsigned int start_index, \
	unsigned int end_index)
{
	char			**cmd_and_args;
	unsigned int	n_cmd;
	unsigned int	i;

	n_cmd = count_tokens_for(command_tokens, start_index, end_index, "cmd");
	cmd_and_args = (char **)malloc(sizeof(char *) * (n_cmd + 1));
	i = 0;
	while (start_index < end_index)
	{
		if (is_redirection(command_tokens[start_index]))
			start_index++;
		else
		{
			cmd_and_args[i] = ft_strdup(command_tokens[start_index]);
			i++;
		}
		start_index++;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}

char	**put_redirections(char **command_tokens, unsigned int start_index, \
	unsigned int end_index)
{
	char			**redir;
	unsigned int	n_redir;
	unsigned int	i;

	n_redir = count_tokens_for(command_tokens, start_index, end_index, "redir");
	redir = (char **)malloc(sizeof(char *) * (n_redir + 1));
	i = 0;
	while (start_index < end_index)
	{
		if (is_redirection(command_tokens[start_index]))
		{
			redir[i] = ft_strdup(command_tokens[start_index]);
			redir[i + 1] = ft_strdup(command_tokens[start_index + 1]);
			start_index++;
			i += 2;
		}
		start_index++;
	}
	redir[i] = NULL;
	return (redir);
}
