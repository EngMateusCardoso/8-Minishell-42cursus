/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:59:39 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/13 16:57:54 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

short int  is_redirection_or_pipe(char *token)
{
    if (token == NULL)
        return (0);
    if (ft_strncmp(token, ">", 1) == 0 || ft_strncmp(token, "<", 1) == 0 || \
        ft_strncmp(token, "|", 1) == 0 || ft_strncmp(token, ">>", 2) == 0 || \
        ft_strncmp(token, "<<", 2) == 0 || ft_strncmp(token, "||", 2) == 0)
        return (1);
    return (0);
}

void	error_msg(char *cmd, char *msg, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	g_data.exit_code = status;
}

void	error_handler(char *str1, char *str2, int status, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	perror("");
	g_data.exit_code = status;
}

short int    syntax_error(char **command_tokens, char *token)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
    ft_putstr_fd(token, 2);
    ft_putchar_fd('\'', 2);
    ft_putstr_fd("\n", 2);
    free_command_tokens(command_tokens);
    g_data.exit_code = 127;
    return (0);
}

short int    check_syntax(char   **command_tokens)
{
    int    i;

    if (command_tokens == NULL)
        return (0);
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
