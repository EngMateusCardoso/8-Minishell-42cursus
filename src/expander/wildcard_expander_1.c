/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:06:33 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:52:27 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_wildcard(char **new_token, char *token, int *j)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*shrunk;

	dir = opendir(".");
	shrunk = shrink_asterisks(token);
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent != NULL)
		{
			if (ft_strncmp(dirent->d_name, ".", 1) != 0)
			{
				if (has_match(dirent->d_name, shrunk))
					new_token[(*j)++] = ft_strdup(dirent->d_name);
			}
			dirent = readdir(dir);
		}
		closedir(dir);
	}
	if (shrunk != NULL)
		ft_free_pointer((void *)&shrunk);
}

int	has_match(char *str, char *shrunk)
{
	if (ft_strncmp(shrunk, "*", 2) == 0)
		return (1);
	mask_asterisks(str);
	if (!match_init_and_end_asterisks(str, shrunk))
		return (0);
	if (!match_randon_asterisks(str, shrunk))
		return (0);
	return (1 && unmask_asterisks(str));
}

int	match_init_and_end_asterisks(char *str, char *shrunk)
{
	if (!(shrunk[0] == '*') && !match_init_asterisk(str, shrunk))
		return (0 && unmask_asterisks(str));
	if (!(shrunk[ft_strlen(shrunk) - 1] == '*') && \
		!match_end_asterisk(str, shrunk))
		return (0 && unmask_asterisks(str));
	return (1);
}

int	match_init_asterisk(char *str, char *shrunk)
{
	int	i;

	i = 0;
	while (shrunk[i] && shrunk[i] != '*')
		i++;
	if (ft_strncmp(str, shrunk, i) == 0)
		return (1);
	else
		return (0);
}

int	match_end_asterisk(char *str, char *shrunk)
{
	int	tk_end;
	int	n;

	if (!shrunk)
		return (0);
	n = 0;
	tk_end = ft_strlen(shrunk);
	while (shrunk[--tk_end] != '*' && tk_end >= 0)
		n++;
	if (ft_strncmp(&str[ft_strlen(str) - n], &shrunk[tk_end + 1], n) == 0)
		return (1);
	else
		return (0);
}
