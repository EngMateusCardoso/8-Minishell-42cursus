/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:34:38 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/24 12:13:53 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void    init_minishell(char **envp)
{
    ft_putstr_fd("Hello minishell!\n", 1);
    store_env_variables(envp);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 1 && argv)
		return (1);
    init_minishell(envp);
    start_minishell();
    finish_minishell();
    return 0;
}
