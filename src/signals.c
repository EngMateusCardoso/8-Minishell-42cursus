/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:56:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/18 10:48:11 by thabeck-         ###   ########.fr       */
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
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
