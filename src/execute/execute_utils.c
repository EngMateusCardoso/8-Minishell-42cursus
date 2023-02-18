/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:29:58 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 00:23:08 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

short int	is_redirection(char *token)
{
	if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
		ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0)
		return (1);
	return (0);
}

unsigned int	redirection_and_pipe_size(char const *command, unsigned int i)
{
	if ((command[i] == '>' && command[i + 1] == '>') || \
		(command[i] == '<' && command[i + 1] == '<'))
		return (2);
	else if (command[i] == '>' || command[i] == '<' || command[i] == '|')
		return (1);
	return (0);
}

short int	is_redirection_or_pipe(char *token)
{
	if (token == NULL)
		return (0);
	if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
		ft_strncmp(token, "|", 1) == 0 || ft_strncmp(token, ">>", 2) == 0 || \
		ft_strncmp(token, "<<", 2) == 0 || ft_strncmp(token, "||", 2) == 0)
		return (1);
	return (0);
}
