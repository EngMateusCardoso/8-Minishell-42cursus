/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:39:01 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/26 17:58:28 by matcardo         ###   ########.fr       */
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

	fd = open_fd_heredoc(n_cmd);
	if (fd < 0)
		write(2, "Error opening file\n", 19);
	while (1)
	{
		line = readline("> ");
		if (!line)
			finish_eof_heredoc(stop_str, line);
		if (ft_strncmp(line, stop_str, ft_strlen(stop_str)) == 0 && \
			ft_strlen(line) == ft_strlen(stop_str))
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

int	open_fd_heredoc(int n_cmd)
{
	int		fd;
	char	*file;
	char	*temp;

	temp = ft_itoa(n_cmd);
	file = ft_strjoin("/tmp/inputfile", temp);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(temp);
	free(file);
	return (fd);
}

void	finish_eof_heredoc(char *stop_str, char *line)
{
	finish_free();
	free(line);
	eof_msg(stop_str);
	exit (0);
}
