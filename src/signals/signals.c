/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 07:56:12 by thabeck-          #+#    #+#             */
/*   Updated: 2023/02/26 17:44:54 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	capture_child_signals(int pid, int is_heredoc)
{
	struct sigaction	sint;
	struct sigaction	squit;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	sint.sa_mask = mask;
	if (pid == 0)
	{
		if (is_heredoc)
			sint.sa_handler = handler_signal_child_heredoc;
		else
			sint.sa_handler = handler_signal_child_exec;
	}
	else
		sint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sint, NULL);
	squit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &squit, NULL);
}
