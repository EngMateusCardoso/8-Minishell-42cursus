/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:34:38 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/10 18:53:59 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	g_data;

void    init_minishell(char **envp)
{
    store_env_variables(envp);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 1 && argv)
		return (1);
    init_minishell(envp);
    start_minishell();
    // char *prompt_input;

	// prompt_input = "teste";
    // ft_putstr_fd("Hello minishell!\n", 1);
    // while (ft_strncmp(prompt_input, "exit", 5))
    // {
    //     prompt_input = readline("minishell$ ");
    // }
	// ft_putstr_fd("Bye minishell \n", 1);
    return 0;
}
