/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 21:22:59 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/21 20:07:27 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_redirections(char **redir_and_files, int i)
{
	int		j;
	char	*file;

	j = 0;
	while (redir_and_files[j])
	{
		file = redir_and_files[j + 1];
		set_redirection_in_pipeline(redir_and_files[j], file, i);
		j++;
	}
	if (i != 0 || has_input_redirection(redir_and_files))
		dup2(g_data.pipes_pids->pipes[i][0], STDIN_FILENO);
	if (i != (g_data.pipes_pids->total_cmd - 1) || \
		has_output_redirection(redir_and_files))
		dup2(g_data.pipes_pids->pipes[i + 1][1], STDOUT_FILENO);
	close(g_data.pipes_pids->pipes[i][0]);
	close(g_data.pipes_pids->pipes[i + 1][1]);
}

void	set_redirection_in_pipeline(char *redir, char *file, int i)
{
	if (redir[0] == '>')
	{
		if (redir[1] == '>')
			g_data.pipes_pids->pipes[i + 1][1] = \
				open_file(file, O_WRONLY | O_CREAT | O_APPEND);
		else
			g_data.pipes_pids->pipes[i + 1][1] = \
				open_file(file, O_WRONLY | O_CREAT | O_TRUNC);
	}
	else if (redir[0] == '<')
	{
		if (redir[1] == '<')
			g_data.pipes_pids->pipes[i][0] = open_heredoc_file(file, i);
		else
			g_data.pipes_pids->pipes[i][0] = open_file(file, O_RDONLY);
	}
}

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("'No such file or directory\n", 2);
	}
	return (fd);
}

int	has_input_redirection(char **redir_and_files)
{
	int	i;

	i = 0;
	while (redir_and_files[i])
	{
		if (redir_and_files[i][0] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	has_output_redirection(char **redir_and_files)
{
	int	i;

	i = 0;
	while (redir_and_files[i])
	{
		if (redir_and_files[i][0] == '>')
			return (1);
		i++;
	}
	return (0);
}
