/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:56:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/19 12:04:53 by thabeck-         ###   ########.fr       */
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

void	capture_exec_signals(int pid)
{
	struct sigaction	sa;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sa.sa_mask = mask;
	if (pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	capture_heredoc_signals(int pid)
{
	struct sigaction	sint;
	struct sigaction	squit;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigemptyset(&sint.sa_mask);
	sint.sa_mask = mask;
	sint.sa_mask = mask;
	if (pid == 0)
		sint.sa_handler = SIG_DFL;
	else
		sint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &squit, NULL);
}
