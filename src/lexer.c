/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 16:51:25 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/13 17:52:09 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	*put_slices(char const *command, int str_index)
{
	int		count_str;
	int		start;
	int		end;
	char	*str;

	end = 0;
	count_str = 0;
	while (command[end] && count_str <= str_index)
	{
		if (command[end] != ' ' && command[end])
		{
			start = end;
            if (command[end] == '"')
            {
                end++;
                while (command[end] != '"' && command[end])
                    end++;
            }
            if (command[end] == '\'')
            {
                end++;
                while (command[end] != '\'' && command[end])
                    end++;
            }
			count_str++;
			while (command[end] != ' ' && command[end])
				end++;
		}
		else
			end++;
	}
	str = (char *)malloc((end - start + 1) * sizeof(char));
	// str = ft_strdup((char *)(command + start));
	ft_strlcpy((char *)str, (char *)(command + start), (size_t)(end - start + 1));
	return (str);
}

unsigned int	countwords(char const *command)
{
	unsigned int	i;
	unsigned int	count_strs;

	i = 0;
	count_strs = 0;
	while (command[i])
	{
		if (command[i] != ' ' && command[i])
		{
            if (command[i] == '"')
            {
                i++;
                while (command[i] != '"' && command[i])
                    i++;
            }
            if (command[i] == '\'')
            {
                i++;
                while (command[i] != '\'' && command[i])
                    i++;
            }
			while (command[i] != ' ' && command[i])
				i++;
			count_strs++;
		}
		else
			i++;
	}
	return (count_strs);
}

char    **lexer(char *command)
{
	unsigned int	count_strs;
	unsigned int	count_str;
	char			**split;

	if (!command)
		return (NULL);
	count_strs = countwords(command);
	split = (char **)malloc((count_strs + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	count_str = 0;
	while (count_str < count_strs)
	{
		split[count_str] = put_slices(command, count_str);
		count_str++;
	}
	split[count_str] = NULL;
	return (split);
}
