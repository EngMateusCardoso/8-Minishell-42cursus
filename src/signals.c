/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:56:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/22 23:37:17 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	capture_signals(struct sigaction *sint, struct sigaction *squit)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sint->sa_mask = mask;
	sint->sa_handler = handler_signal;
	sigaction(SIGINT, sint, NULL);
	squit->sa_mask = mask;
	squit->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, squit, NULL);
}

void	handler_signal(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	capture_child_signals(int pid)
{
	struct sigaction	sint;
	struct sigaction	squit;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sint.sa_mask = mask;
	if (pid == 0)
		sint.sa_handler = handler_signal_child;
	else
		sint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &squit, NULL);
}

void	handler_signal_child(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(2, "\n", 1);
	finish_free();
	exit (130);
}

void	handler_signal_parent(int sig)
{
	(void)sig;
	g_data.exit_code = 130;
	write(2, "\n", 1);
}
