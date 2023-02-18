/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:08:05 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:52:36 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	match_randon_asterisks(char *str, char *shrunk)
{
	int		i;
	size_t	len;
	int		indexes[2];
	char	*fragment;

	i = 0;
	indexes[1] = 0;
	while (shrunk[i])
	{
		len = 0;
		if (shrunk[i] == '*')
			i++;
		indexes[0] = i;
		while (shrunk[i] && shrunk[i] != '*')
		{
			i++;
			len++;
		}
		fragment = ft_substr(shrunk, indexes[0], len);
		if (!find_randon_match(&str[indexes[1]], fragment, len, &indexes[1]))
			return (0 && unmask_asterisks(str));
	}
	return (1);
}

int	find_randon_match(char *str, char *fragment, size_t len, int *index)
{
	int	i;

	i = 0;
	if (!str || !fragment)
		return (0);
	while (str[i] && ft_strlen(&str[i]) >= len)
	{
		if (ft_strncmp(&str[i], fragment, len) == 0)
		{
			*index += (i + len);
			ft_free_pointer((void *)&fragment);
			return (1);
		}
		i++;
	}
	ft_free_pointer((void *)&fragment);
	return (0);
}

char	*shrink_asterisks(char *token)
{
	int		i;
	char	*shrunk;

	i = 0;
	shrunk = NULL;
	while (token[i])
	{
		if (token[i] == '*')
		{
			while (token[i] && token[i] == '*')
				i++;
			shrunk = ft_straddchar(shrunk, '*');
		}
		while (token[i] && token[i] != '*')
			shrunk = ft_straddchar(shrunk, token[i++]);
		if (!token[i])
			break ;
	}
	return (shrunk);
}
