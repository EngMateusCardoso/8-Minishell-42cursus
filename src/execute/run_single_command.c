/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_single_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:27:53 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 06:36:04 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_single_command(char **cmd_and_args)
{
	char	*cmd_path;
	char	*str_error;

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
	paths = ft_split(getenv("PATH"), ':');
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
