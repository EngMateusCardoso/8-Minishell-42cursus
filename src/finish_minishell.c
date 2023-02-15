/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:24:22 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/14 21:50:50 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_closing(void)
{
	int		fd;
	char	buff[1];
	int		idx;

	fd = open("./src/assets/closing.txt", O_RDONLY);
	if (fd == -1)
		return ;
    printf("\n");
	idx = 0;
	while (read(fd, buff, 1))
	{
		if (idx < 74)
			print_color_char(idx, buff[0]);
		else
		{
			idx = 0;
			print_color_char(idx, buff[0]);
		}
		idx++;
	}
    printf("\n");
	close(fd);
	return ;
}

void    finish_free(void)
{
    free_hash_table();
}

void    finish_minishell(void)
{
    finish_free();
	rl_clear_history();
    print_closing();
}
