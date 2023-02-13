/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:47:14 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/11 18:59:06 by thabeck-         ###   ########.fr       */
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

void    print_command_table(t_cmd *command_table)
{
    int i;
    int j;

    i = 0;
    j = 0;
    ft_putstr_fd("command_table test:\n", 1);
    while (command_table[i].cmd_and_args || command_table[i].redirections_and_files)
    {
        while (command_table[i].cmd_and_args[j])
        {
            ft_putstr_fd("-", 1);
            ft_putstr_fd(command_table[i].cmd_and_args[j], 1);
            j++;
        }
        j = 0;
        while (command_table[i].redirections_and_files[j])
        {
            ft_putstr_fd(">", 1);
            ft_putstr_fd(command_table[i].redirections_and_files[j], 1);
            j++;
        }
        j = 0;
        ft_putstr_fd("\n", 1);
        i++;
    }
}

