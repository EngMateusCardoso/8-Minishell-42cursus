/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:44:35 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/18 10:51:17 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_command_tokens(char **command_tokens)
{
	int	i;

	i = 0;
	while (command_tokens[i])
		free(command_tokens[i++]);
	free(command_tokens[i]);
	free(command_tokens);
}

void	free_command_table(t_cmd *command_table)
{
	int	i;
	int	j;

	i = 0;
	while (command_table[i].cmd_and_args || \
		command_table[i].redirections_and_files)
	{
		j = 0;
		while (command_table[i].cmd_and_args[j])
			free(command_table[i].cmd_and_args[j++]);
		free(command_table[i].cmd_and_args[j]);
		j = 0;
		while (command_table[i].redirections_and_files[j])
			free(command_table[i].redirections_and_files[j++]);
		free(command_table[i].redirections_and_files[j]);
		free(command_table[i].cmd_and_args);
		free(command_table[i].redirections_and_files);
		i++;
	}
	free(command_table[i].cmd_and_args);
	free(command_table[i].redirections_and_files);
	free(command_table);
}

void	free_pipes_and_pids(void)
{
	int	i;

	i = 0;
	while (g_data.pipes_pids->pipes[i])
		free(g_data.pipes_pids->pipes[i++]);
	free(g_data.pipes_pids->pipes);
	free(g_data.pipes_pids->pids);
	free(g_data.pipes_pids);
}

void	free_hash_table(void)
{
	int		i;
	t_list	*temp;
	t_list	*temp2;

	i = 0;
	while (i < TABLE_SIZE)
	{
		temp = g_data.hash_table[i];
		while (temp)
		{
			temp2 = temp->next;
			free(((t_env_var *)temp->content)->key);
			free(((t_env_var *)temp->content)->value);
			free(temp->content);
			free(temp);
			temp = temp2;
		}
		i++;
	}
}
