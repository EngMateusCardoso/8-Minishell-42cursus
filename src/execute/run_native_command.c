/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:27:53 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/22 21:48:42 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_native_command(char **cmd_and_args)
{
	char	*cmd_path;
	char	*str_error;

	if (!cmd_and_args[0])
	{
		finish_free();
		exit(0);
	}
	cmd_path = get_command_path(cmd_and_args[0]);
	if (!cmd_path)
	{
		str_error = ft_strjoin(cmd_and_args[0], ": command not found\n");
		write(2, str_error, ft_strlen(str_error));
		free(str_error);
		free(cmd_path);
		finish_free();
		exit(127);
	}
	execve(cmd_path, cmd_and_args, g_data.envp);
}

char	*get_command_path(char *cmd)
{
	char	*target;
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	if (!ft_strncmp(cmd, "/bin/", 5) && access(cmd, F_OK) == 0)
		return (cmd);
	paths = ft_split(find_hash_var(g_data.hash_table[hash_function("PATH") \
				% TABLE_SIZE], "PATH"), ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		target = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(target, F_OK) == 0)
		{
			free_paths(paths);
			return (target);
		}
		free(target);
		i++;
	}
	free_paths(paths);
	return (NULL);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
