/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:24:22 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/26 18:06:52 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	finish_minishell(void)
{
	print_closing();
	finish_free();
}

void	finish_free(void)
{
	free_hash_table();
	free(g_data.root_path);
	free(g_data.home_path);
	rl_clear_history();
	free_command_table(g_data.command_table_expanded);
	free_pipes_and_pids();
}

void	prompt_eof_finish(char *prompt_input)
{
	print_closing();
	free_hash_table();
	free(g_data.root_path);
	free(g_data.home_path);
	rl_clear_history();
	free(prompt_input);
	exit(2);
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
