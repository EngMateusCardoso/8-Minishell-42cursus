/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 11:24:22 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/26 09:57:29 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_closing(void)
{
	int		fd;
	char	buff[1];

	fd = open("./src/closing.txt", O_RDONLY);
	if (fd == -1)
		return ;
    printf("\n");
	while (read(fd, buff, 1))
	    printf("%c", buff[0]);
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
    print_closing();
}
