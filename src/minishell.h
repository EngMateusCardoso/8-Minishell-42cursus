/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:52:56 by matcardo          #+#    #+#             */
/*   Updated: 2022/12/10 20:44:32 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "../libraries/libft/libft.h"

# define TABLE_SIZE 50

typedef struct s_env_var
{
    char        *key;
    char        *value;
}               t_env_var;

typedef struct s_data
{
    t_list      *(hash_table[TABLE_SIZE]);
}               t_data;

extern t_data   g_data;

void    store_env_variables(char **envp);
void    start_minishell(void);
int     is_builtin(char *command);
void    execute_builtin(char *command);

#endif