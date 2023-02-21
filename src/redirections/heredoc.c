/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:39:01 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/21 14:55:59 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc(t_cmd *command_table)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (command_table[i].redirections_and_files)
	{
		j = 0;
		while (command_table[i].redirections_and_files[j])
		{
			if (ft_strncmp(command_table[i].redirections_and_files[j], \
				"<<", 2) == 0)
			{
				init_heredoc(command_table[i].redirections_and_files[j + 1], i);
			}
			j++;
		}
		i++;
	}
}

void	init_heredoc(char *stop_str, int n_cmd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid < 0)
		write(2, "Error forking\n", 14);
	capture_child_signals(pid, 1);
	if (pid == 0)
		open_heredoc(stop_str, n_cmd);
	waitpid(-1, &wstatus, 0);
	g_data.exit_code = WEXITSTATUS(wstatus);
}

void	open_heredoc(char *stop_str, int n_cmd)
{
	char	*line;
	int		fd;
	char	*file;
	char	*temp;

	temp = ft_itoa(n_cmd);
	file = ft_strjoin("/tmp/inputfile", temp);
	free(temp);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (fd < 0)
		write(2, "Error opening file\n", 19);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			finish_free();
			free(line);
			eof_msg(stop_str);
			exit (130);
		}
		if (ft_strncmp(line, stop_str, ft_strlen(stop_str)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	finish_open_heredoc(fd);
}

void	finish_open_heredoc(int fd)
{
	close(fd);
	g_data.exit_code = 0;
	finish_free();
	exit(0);
}

int	open_fd_heredoc(char *file, int n_cmd)
{
	char	*temp;
	int		fd;

	temp = ft_itoa(n_cmd);
	file = ft_strjoin("/tmp/inputfile", temp);
	free(temp);
	fd = open(file, O_RDONLY, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("'No such file or directory\n", 2);
	}
	free(file);
	return (fd);
}
