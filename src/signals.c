/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:56:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/20 12:15:24 by thabeck-         ###   ########.fr       */
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

void	capture_child_signals(int pid, int need_free)
{
	struct sigaction	sint;
	struct sigaction	squit;
	sigset_t			mask;

	if (need_free)
	{
		//add free aqui
	}
	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sigemptyset(&sint.sa_mask);
	sint.sa_mask = mask;
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
	exit (130);
}

void	handler_signal_father(int sig)
{
	(void)sig;
	write(2, "\n", 1);
}
