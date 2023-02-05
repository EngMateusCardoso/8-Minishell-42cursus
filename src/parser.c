/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:30:32 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/03 20:10:03 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    count_tokens_for(char **command_tokens, int start_index, int end_index, char *type)
{
    int     i;
    int     n_cmd;
    int     n_redir;

    i = start_index;
    n_cmd = 0;
    n_redir = 0;
    while (i < end_index)
    {
        if (is_redirection(command_tokens[i]))
        {
            n_redir += 2;
            i++;
        }
        else
            n_cmd += 1;
        i++;
    }
    if (ft_strncmp(type, "cmd", 3) == 0)
        return (n_cmd);
    else if (ft_strncmp(type, "redir", 5) == 0)
        return (n_redir);
    return (0);
}

char    **put_cmd_and_args(char **command_tokens, int start_index, int end_index)
{
    char    **cmd_and_args;
    int     n_cmd;
    int     i;

    n_cmd = count_tokens_for(command_tokens, start_index, end_index, "cmd");
    ft_putstr_fd("n_cmd: ", 1);
    ft_putnbr_fd(n_cmd, 1);
    ft_putchar_fd('\n', 1);
    cmd_and_args = (char **)malloc(sizeof(char *) * (n_cmd + 1));
    i = 0;
    while (start_index < end_index)
    {
        if (is_redirection(command_tokens[start_index]))
            start_index++;
        else
        {
            cmd_and_args[i] = ft_strdup(command_tokens[start_index]);
            i++;
        }
        start_index++;
    }
    cmd_and_args[i] = NULL;
    return (cmd_and_args);
}

char    **put_redirections(char **command_tokens, int start_index, int end_index)
{
    char    **redir;
    int     n_redir;
    int     i;

    n_redir = count_tokens_for(command_tokens, start_index, end_index, "redir");
    ft_putstr_fd("n_redir: ", 1);
    ft_putnbr_fd(n_redir, 1);
    ft_putchar_fd('\n', 1);
    redir = (char **)malloc(sizeof(char *) * (n_redir + 1));
    i = 0;
    while (start_index < end_index)
    {
        if (is_redirection(command_tokens[start_index]))
        {
            redir[i] = ft_strdup(command_tokens[start_index]);
            redir[i + 1] = ft_strdup(command_tokens[start_index + 1]);
            start_index++;
            i += 2;
        }
        start_index++;
    }
    redir[i] = NULL;
    return (redir);
}

t_cmd   put_complete_cmd(char **command_tokens, int index_table)
{
    t_cmd   complete_cmd;
    int     end_index;
    int     start_index;
    int     i;

    i = 0;
    start_index = 0;
    while (i < index_table)
    {
        if (ft_strncmp(command_tokens[start_index], "|", 1) == 0)
            i++;
        start_index++;
    }
    end_index = start_index;
    while (command_tokens[end_index] && ft_strncmp(command_tokens[end_index], "|", 1) != 0)
        end_index++;
    ft_putstr_fd("-----------\n", 1);
    ft_putstr_fd("Index_table: ", 1);
    ft_putnbr_fd(index_table, 1);
    ft_putchar_fd('\n', 1);
    ft_putstr_fd("start_index: ", 1);
    ft_putnbr_fd(start_index, 1);
    ft_putchar_fd('\n', 1);
    ft_putstr_fd("end_index: ", 1);
    ft_putnbr_fd(end_index, 1);
    ft_putchar_fd('\n', 1);
    i = 0;
    complete_cmd.cmd_and_args = put_cmd_and_args(command_tokens, start_index, end_index);
    complete_cmd.redirections_and_files = put_redirections(command_tokens, start_index, end_index);
    return (complete_cmd);
}

size_t  get_command_table_size(char   **command_tokens)
{
    size_t  size;
    int     i;

    size = 0;
    i = 0;
    while (command_tokens[i])
    {
        if (ft_strncmp(command_tokens[i], "|", 1) == 0)
            size++;
        i++;
    }
    return (size + 1);
}

t_cmd   *parser(char   **command_tokens)
{
    t_cmd   *command_table;
    int     cmd_table_size;
    int     index_table;

    cmd_table_size = get_command_table_size(command_tokens);
    command_table = (t_cmd *)malloc(sizeof(t_cmd) * (cmd_table_size + 1));
    index_table = 0;
    while (index_table < cmd_table_size)
    {
        command_table[index_table] = put_complete_cmd(command_tokens, index_table);
        index_table++;
    }
    command_table[index_table].cmd_and_args = NULL;
    command_table[index_table].redirections_and_files = NULL;
    return (command_table);
}
