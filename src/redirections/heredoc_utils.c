/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:04:40 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/21 20:20:07 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_heredoc_file(char *file, int n_cmd)
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

void	finish_open_heredoc(int fd)
{
	close(fd);
	g_data.exit_code = 0;
	finish_free();
	exit(0);
}
