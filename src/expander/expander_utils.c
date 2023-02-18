/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:22:13 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:52:01 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_commands(t_cmd *command_table)
{
	int	i;

	i = 0;
	while (command_table[i].cmd_and_args || \
		command_table[i].redirections_and_files)
		i++;
	return (i);
}

int	count_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (has_wildcard(args[i]))
			j += count_wildcards(args[i]);
		else
			j++;
		i++;
	}
	return (j);
}

int	count_wildcards(char *token)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*shrunk;
	int				i;

	dir = opendir(".");
	i = 0;
	shrunk = shrink_asterisks(token);
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent != NULL)
		{
			if (ft_strncmp(dirent->d_name, ".", 1) != 0)
				if (has_match(dirent->d_name, shrunk))
					i++;
			dirent = readdir(dir);
		}
		closedir(dir);
	}
	ft_free_pointer((void *)&shrunk);
	return (i);
}
