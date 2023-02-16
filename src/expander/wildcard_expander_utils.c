/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:11:19 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/16 10:16:44 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_wildcard(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] == '\'')
		{
			while (var[++i] && var[i] != '\'')
				continue ;
			if (var[i])
				i++;
		}
		if (var[i] == '\"')
		{
			while (var[++i] && var[i] != '\"')
				continue ;
			if (var[i])
				i++;
		}
		if (var[i] == '*')
			return (1);
		if (!var[i])
			break ;
	}
	return (0);
}

void	mask_asterisks(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
			str[i] = 1;
	}
}

int	unmask_asterisks(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 1)
			str[i] = '*';
	}
	return (1);
}
