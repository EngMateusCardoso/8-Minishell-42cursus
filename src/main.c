/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:34:38 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/09 17:40:28 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *prompt_input;
    ft_putstr_fd("Hello minishell!", 1);
    while (!ft_strncmp(prompt_input, "exit", 5))
    {
        prompt_input = readline("minishell$ ");
    }
    return 0;
}
