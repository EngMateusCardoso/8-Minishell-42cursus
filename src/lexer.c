/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:51:25 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/14 15:58:21 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

unsigned int redirection_and_pipe_size(char const *command, unsigned int i)
{
	if ((command[i] == '>' && command[i + 1] == '>') || \
	 (command[i] == '<' && command[i + 1] == '<') || 
	 (command[i] == '|' && command[i + 1] == '|'))
		return (2);
	else if (command[i] == '>' || command[i] == '<' || command[i] == '|')
		return (1);
	return (0);
}

unsigned int	quote_token_size(char const *command, unsigned int i, const char quote_type)
{
	unsigned int	size;

	size = 1;
	i++;
	while (command[i] && command[i] != quote_type)
	{
		size++;
		i++;
	}
	if (command[i] == quote_type)
		size++;
	return (size);
}

unsigned int	token_size(char const *command, unsigned int i)
{
	unsigned int	size;

	size = 0;
	if (command[i] && (command[i] == '"' || command[i] == '\''))
		return (quote_token_size(command, i, command[i]));
	if (redirection_and_pipe_size(command, i) > 0)
		return (redirection_and_pipe_size(command, i));
	while (command[i] && command[i] != ' ' && \
		redirection_and_pipe_size(command, i) == 0 && command[i] != '"' \
		&& command[i] != '\'')
	{
		size++;
		i++;
	}
	return (size);
}

char	*put_slices(char const *command, unsigned int token_index)
{
	unsigned int	i;
	unsigned int	count_tokens;

	i = 0;
	count_tokens = 0;
	while (command[i] && count_tokens < token_index)
	{
		while (command[i] && command[i] == ' ')
			i++;
		if (token_size(command, i) > 0)
			count_tokens++;
		i += token_size(command, i);
	}
	while (command[i] && command[i] == ' ')
		i++;
	return (ft_substr(command, i, token_size(command, i)));

}

unsigned int	to_count_tokens(char const *command)
{
	unsigned int	i;
	unsigned int	count_tokens;

	i = 0;
	count_tokens = 0;
	while (command[i])
	{
		while (command[i] && command[i] == ' ')
			i++;
		if (token_size(command, i) > 0)
			count_tokens++;
		i += token_size(command, i);
	}
	return (count_tokens);
}

char    **lexer(char *command)
{
	unsigned int	count_tokens;
	unsigned int	count_token;
	char			**split;

	if (!command)
		return (NULL);
	count_tokens = to_count_tokens(command);
	split = (char **)malloc((count_tokens + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	count_token = 0;
	ft_putnbr_fd(count_tokens, 1);
	ft_putstr_fd("\n", 1);
	while (count_token < count_tokens)
	{
		split[count_token] = put_slices(command, count_token);
		count_token++;
	}
	split[count_token] = NULL;
	return (split);
}
