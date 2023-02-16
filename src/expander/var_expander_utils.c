/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:04:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/16 10:06:09 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_varkey(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

int	can_expand(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] && var[i] == '\'')
		{
			i++;
			while (var[i] && var[i] != '\'')
				i++;
		}
		else if (var[i] && var[i] == '\"')
		{
			i++;
			while (var[i] && var[i] != '\"')
				if (var[i++] == '$')
					return (1);
		}
		else if (var[i] && (var[i] == '$' || ft_strncmp(var, "~", 2) == 0))
			return (1);
		if (var[i])
			i++;
	}
	return (0 || has_wildcard(var));
}

int	single_mark_case(char *token, char **expanded)
{
	int	i;

	i = 1;
	while (token[i] && token[i] != '\'')
	{
		*expanded = ft_straddchar(*expanded, token[i]);
		i++;
	}
	return (i);
}

int	double_mark_case(char *token, char **expanded)
{
	int	i;

	i = 0;
	while (token[++i] && token[i] != '\"')
	{
		if (token[i] == '$')
			i += expand_var(expanded, &token[i + 1]);
		else
			*expanded = ft_straddchar(*expanded, token[i]);
	}
	return (i);
}
