/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:59:39 by matcardo          #+#    #+#             */
/*   Updated: 2023/01/24 20:51:28 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int    syntax_error(char **command_tokens, char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putchar_fd('\'', 2);
    ft_putstr_fd("\n", 2);
    free_command_tokens(command_tokens);
    return (0);
}

short int    is_redirection(char *token)
{
    if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
        ft_strncmp(token, ">>", 2) == 0 || ft_strncmp(token, "<<", 2) == 0)
        return (1);
    return (0);
}

short int    check_syntax(char   **command_tokens)
{
    int    i;

    if (ft_strncmp(command_tokens[0], "|", 1) == 0)
        return (syntax_error(command_tokens, command_tokens[0]));
    i = 0;
    while (command_tokens[i])
    {
        if (ft_strncmp(command_tokens[i], "|", 1) == 0 && \
            command_tokens[i + 1] && \
            ft_strncmp(command_tokens[i + 1], "|", 1) == 0)
            return (syntax_error(command_tokens, command_tokens[i + 1]));
        if (is_redirection(command_tokens[i]) && \
            is_redirection_or_pipe(command_tokens[i + 1]))
            return (syntax_error(command_tokens, command_tokens[i + 1]));
        i++;
    }
    if (is_redirection_or_pipe(command_tokens[i - 1]) && !command_tokens[i])
        return (syntax_error(command_tokens, "newline"));
    return (1);
}
