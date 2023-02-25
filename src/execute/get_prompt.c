/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:05:16 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/25 00:01:48 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_prompt(void)
{
	char	*prompt;
	char	*path;
	char	*tmp;
	char	*tmp2;

	prompt = get_str_prompt();
	path = get_str_path();
	tmp = ft_strjoin(prompt, path);
	tmp2 = ft_strjoin(tmp, RESET_PROMPT);
	free(path);
	free(prompt);
	free(tmp);
	return (tmp2);
}

char	*get_str_prompt(void)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(getenv("USER"), "@minishell:");
	prompt = ft_strjoin(PROMPT_COLOR, tmp);
	free(tmp);
	return (prompt);
}

char	*get_str_path(void)
{
	char	*path;
	char	*home;
	char	*tmp;
	char	*tmp2;

	path = getcwd(NULL, 0);
	home = find_hash_var(g_data.hash_table[hash_function("HOME") \
				% TABLE_SIZE], "HOME");
	if (home && ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", &path[ft_strlen(home)]);
		tmp2 = ft_strjoin(PATH_COLOR, tmp);
		free(path);
		free(tmp);
		return (tmp2);
	}
	else
	{
		tmp = ft_strjoin(PATH_COLOR, path);
		free(path);
		return (tmp);
	}
}
