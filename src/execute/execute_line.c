/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   start_minishell.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: matcardo <matcardo@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/12/10 18:54:15 by matcardo		  #+#	#+#			 */
/*   Updated: 2023/02/16 15:03:28 by matcardo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_line(char *command)
{
	char	**command_tokens;
	t_cmd	*command_table;

	command_tokens = lexer(command);
	free(command);
	if (check_syntax(command_tokens))
	{
		init_pipes_and_pids(count_pipes(command_tokens));
		command_table = parser(command_tokens);
		free_command_tokens(command_tokens);
		g_data.command_table_expanded = expand_command_table(command_table);
		free_command_table(command_table);
		heredoc(g_data.command_table_expanded);
		if (is_forked(g_data.command_table_expanded))
			execute_with_fork(g_data.command_table_expanded);
		else
			execute_no_fork(g_data.command_table_expanded);
		free_command_table(g_data.command_table_expanded);
		free_pipes_and_pids();
	}
}

int	count_pipes(char **command_tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command_tokens[i])
	{
		if (ft_strncmp(command_tokens[i], "|", 1) == 0)
			count++;
		i++;
	}
	return (count);
}

void	init_pipes_and_pids(int n_pipes)
{
	int	i;

	g_data.pipes_pids = malloc(sizeof(t_pipes_pids));
	g_data.pipes_pids->pipes = malloc(sizeof(int *) * (n_pipes + 3));
	g_data.pipes_pids->pids = malloc(sizeof(pid_t) * (n_pipes + 1));
	g_data.pipes_pids->total_cmd = n_pipes + 1;
	i = 0;
	while (i <= n_pipes + 1)
	{
		g_data.pipes_pids->pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(g_data.pipes_pids->pipes[i]) == -1)
			ft_putstr_fd("Error creating pipe\n", 2);
		if (i != n_pipes + 1)
			g_data.pipes_pids->pids[i] = 0;
		i++;
	}
	g_data.pipes_pids->pipes[i] = NULL;
}

short int	is_forked(t_cmd *command_table)
{
	if (command_table[0].cmd_and_args && \
		!(command_table[1].cmd_and_args) && \
		!(command_table[1].redirections_and_files) && \
		command_table[0].cmd_and_args && \
		command_table[0].cmd_and_args[0] && \
		(ft_strncmp(command_table[0].cmd_and_args[0], "exit", 5) == 0 || \
		ft_strncmp(command_table[0].cmd_and_args[0], "cd", 3) == 0 || \
		ft_strncmp(command_table[0].cmd_and_args[0], "export", 7) == 0 || \
		ft_strncmp(command_table[0].cmd_and_args[0], "unset", 6) == 0))
		return (0);
	return (1);
}

void	execute_no_fork(t_cmd *command_table)
{
	set_redirections(command_table[0].redirections_and_files, 0);
	run_builtin(command_table[0].cmd_and_args, 0);
}
