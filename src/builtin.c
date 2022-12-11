/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:32:35 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/10 23:31:23 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    exec_env(void)
{
    int     i;
    t_list  *tmp;

    i = 0;
    while (i < TABLE_SIZE)
    {
        tmp = g_data.hash_table[i];
        while (tmp)
        {
            ft_putstr_fd(((t_env_var *)tmp->content)->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(((t_env_var *)tmp->content)->value, 1);
            ft_putstr_fd("\n", 1);
            tmp = tmp->next;
        }
        i++;
    }
}

int     is_builtin(char *command)
{
    if (!ft_strncmp(command, "echo", 5) || !ft_strncmp(command, "cd", 3)
        || !ft_strncmp(command, "pwd", 4) || !ft_strncmp(command, "export", 7)
        || !ft_strncmp(command, "unset", 6) || !ft_strncmp(command, "env", 4)
        || !ft_strncmp(command, "exit", 5))
            return (1);
    return (0);
}

void    execute_builtin(char *command)
{
    if (!ft_strncmp(command, "echo", 5))
        ft_putstr_fd("echoing\n", 1);
    else if (!ft_strncmp(command, "cd", 3))
        ft_putstr_fd("changing directory\n", 1);
    else if (!ft_strncmp(command, "pwd", 4))
        ft_putstr_fd("printing working directory\n", 1);
    else if (!ft_strncmp(command, "export", 7))
        ft_putstr_fd("exporting\n", 1);
    else if (!ft_strncmp(command, "unset", 6))
        ft_putstr_fd("unsetting\n", 1);
    else if (!ft_strncmp(command, "env", 4))
        exec_env();
    else if (!ft_strncmp(command, "exit", 5))
        ft_putstr_fd("exiting\n", 1);
}
