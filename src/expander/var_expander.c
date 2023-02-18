/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:58:03 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:52:21 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_env_var(char **expand, char *var, int size)
{
	char			*key;
	char			*value;
	char			*tmp;
	unsigned int	idx;

	if (size)
	{
		key = ft_substr(var, 0, size);
		idx = hash_function(key) % TABLE_SIZE;
		value = find_hash_var(g_data.hash_table[idx], key);
		if (value != NULL && value[0] != '\0')
		{
			if (*expand == NULL)
				*expand = ft_strdup(value);
			else
			{
				tmp = *expand;
				*expand = ft_strjoin(tmp, value);
				ft_free_pointer((void *)&tmp);
			}
		}
		ft_free_pointer((void *)&key);
	}
}

int	expand_var(char **expanded, char *var)
{
	int		size;
	char	*value;
	char	*temp;

	size = 0;
	if (var[0] == '?')
	{
		value = ft_itoa(g_data.exit_code);
		temp = *expanded;
		*expanded = ft_strjoin(temp, value);
		ft_free_pointer((void *)&temp);
		ft_free_pointer((void *)&value);
		g_data.exit_code = 0;
		return (1);
	}
	else
	{
		while (var[size] && is_varkey(var[size]) && var[size] != '$')
			size++;
		expand_env_var(expanded, var, size);
		return (size);
	}
}

char	*expand_money_sign(char *var)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup("");
	i = -1;
	while (var[++i])
	{
		if (var[i] == '\'')
			i += single_mark_case(&var[i], &expanded);
		else if (var[i] == '\"')
			i += double_mark_case(&var[i], &expanded);
		else if (var[i] == '$' && is_varkey(var[i + 1]))
			i += expand_var(&expanded, &var[i + 1]);
		else
			expanded = ft_straddchar(expanded, var[i]);
		if (!var[i])
			break ;
	}
	if (!expanded)
	{
		ft_free_pointer((void *)&expanded);
		return (NULL);
	}
	return (expanded);
}

char	*expand_tilde(char *var)
{
	char			*home;
	unsigned int	idx;

	idx = hash_function("HOME") % TABLE_SIZE;
	if (ft_strncmp(var, "~", 2) == 0)
	{
		home = ft_strdup(find_hash_var(g_data.hash_table[idx], "HOME"));
		return (home);
	}
	return (NULL);
}
