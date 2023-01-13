/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:44:35 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/13 17:30:58 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    free_command_tokens(char **command_tokens)
{
    int i;

    i = 0;
    while (command_tokens[i])
    {
        free(command_tokens[i]);
        i++;
    }
    free(command_tokens[i]);
    free(command_tokens);
}

void    free_command_table(char ***command_table)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (command_table[i])
    {
        while (command_table[i][j])
        {
            free(command_table[i][j]);
            j++;
        }
        free(command_table[i][j]);
        free(command_table[i]);
        j = 0;
        i++;
    }
    free(command_table[i]);
    free(command_table);
}
