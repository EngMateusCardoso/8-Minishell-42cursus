/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:29:34 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/26 17:44:48 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handler_signal(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_signal_parent(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(2, "\n", 1);
}

void	handler_signal_child_exec(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(2, "\n", 1);
	finish_free();
	exit (130);
}

void	handler_signal_child_heredoc(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	g_data.not_run = 1;
	write(2, "\n", 1);
	finish_free();
	exit (130);
}
