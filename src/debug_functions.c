/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:47:14 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/21 20:09:12 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    print_command_tokens(char **command_tokens)
{
    int i;

    i = 0;
    ft_putstr_fd("command_tokens test:\n", 1);
    while (command_tokens[i])
    {
        ft_putstr_fd(command_tokens[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
}

void    print_command_table(char    ***command_table)
{
    int i;
    int j;

    i = 0;
    j = 0;
    ft_putstr_fd("command_table test:\n", 1);
    while (command_table[i])
    {
        while (command_table[i][j])
        {
            ft_putstr_fd("-", 1);
            ft_putstr_fd(command_table[i][j], 1);
            j++;
        }
        ft_putstr_fd("\n", 1);
        j = 0;
        i++;
    }
}

