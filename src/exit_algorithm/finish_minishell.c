/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:24:22 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 12:02:20 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	finish_minishell(void)
{
	finish_free();
	print_closing();
}

void	finish_free(void)
{
	free_hash_table();
	rl_clear_history();
	free_command_table(g_data.command_table_expanded);
	free_pipes_and_pids();
}

void	print_closing(void)
{
	int		fd;
	char	buff[1];
	char	*path;

	path = ft_strjoin(g_data.root_path, "/src/assets/closing.txt");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	printf("\n");
	read_file(buff, fd);
	printf("\n");
	close(fd);
	ft_free_pointer((void *)&path);
	free(g_data.root_path);
	return ;
}

void	read_file(char *buff, int fd)
{
	int		index;

	index = 0;
	while (read(fd, buff, 1))
	{
		if (index < 74)
			print_color_char(index, buff[0]);
		else
		{
			index = 0;
			print_color_char(index, buff[0]);
		}
		index++;
	}
}
