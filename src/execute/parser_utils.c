/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:37:57 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 00:14:21 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned int	count_tokens_for(char **command_tokens, \
	unsigned int start_index, unsigned int end_index, char *type)
{
	unsigned int	i;
	unsigned int	n_cmd;
	unsigned int	n_redir;

	i = start_index;
	n_cmd = 0;
	n_redir = 0;
	while (i < end_index)
	{
		if (is_redirection(command_tokens[i]))
		{
			n_redir += 2;
			i++;
		}
		else
			n_cmd += 1;
		i++;
	}
	if (ft_strncmp(type, "cmd", 3) == 0)
		return (n_cmd);
	else if (ft_strncmp(type, "redir", 5) == 0)
		return (n_redir);
	return (0);
}
