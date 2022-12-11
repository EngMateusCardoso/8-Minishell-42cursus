/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/10 20:40:27 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    start_minishell(void)
{
    char *prompt_input;

    prompt_input = "teste";
    ft_putstr_fd("Hello minishell!\n", 1);
    while (ft_strncmp(prompt_input, "exit", 5))
    {
        prompt_input = readline("minishell$ ");
        if (!ft_strncmp(prompt_input, "show", 5))
            ft_putstr_fd("showing\n", 1);
        else if (is_builtin(prompt_input))
            execute_builtin(prompt_input);
    }
    ft_putstr_fd("Bye minishell \n", 1);
}
