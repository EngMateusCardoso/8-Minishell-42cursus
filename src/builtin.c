/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:32:35 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/13 22:18:54 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *   exit [n]
 *   Exit the shell, returning a status of n to the shell’s parent.
 *   If n is omitted, the exit status is that of the last command executed.
 *   Any trap on EXIT is executed before the shell terminates.
 *   OBS: este comando não faz nada quando tem pipes com outros comandos.
 *   --help para descrição dos cmd
 */

void exec_exit(char **command)
{
	int exit_status;

	exit_status = 0;
	if (command[1])
		exit_status = ft_atoi(command[1]);
	else
		exit_status = 0;
	free_command_table(g_data.command_table_expanded);
	free_pipes_and_pids();
	finish_minishell();
	exit(exit_status);
}

void exec_env(void)
{
	int i;
	t_list *tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = g_data.hash_table[i];
		while (tmp != NULL)
		{
			ft_putstr_fd(((t_env_var *)tmp->content)->key, 1);
			ft_putstr_fd("=", 1);
			if (((t_env_var *)(tmp->content))->value)
				ft_putstr_fd(((t_env_var *)(tmp->content))->value, 1);
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
		i++;
	}
}

int is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", 5) || !ft_strncmp(command, "cd", 3) || !ft_strncmp(command, "pwd", 4) || !ft_strncmp(command, "export", 7) || !ft_strncmp(command, "unset", 6) || !ft_strncmp(command, "env", 4) || !ft_strncmp(command, "exit", 5))
		return (1);
	return (0);
}

void execute_builtin(char **command, int isfork)
{
	if (isfork)
	{
		if (!ft_strncmp(command[0], "echo", 5))
			ft_putstr_fd("echoing\n", 1);
		else if (!ft_strncmp(command[0], "pwd", 4))
			ft_putstr_fd("printing working directory\n", 1);
		else if (!ft_strncmp(command[0], "env", 4))
			exec_env();
	}
	else
	{
		if (!ft_strncmp(command[0], "cd", 3))
			cd_builtin(command[1]);
		else if (!ft_strncmp(command[0], "export", 7))
			export_builtin(command);
		else if (!ft_strncmp(command[0], "unset", 6))
			ft_putstr_fd("unsetting\n", 1);
		else if (!ft_strncmp(command[0], "exit", 5))
			exec_exit(command);
	}
}
