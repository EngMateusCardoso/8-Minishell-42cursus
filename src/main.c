/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:34:38 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/26 18:07:16 by matcardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	g_data;

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 && argv)
		return (1);
	init_minishell(envp);
	start_minishell();
	return (0);
}

void	init_minishell(char **envp)
{
	int		i;
	char	*path;

	print_startup();
	g_data.envp = envp;
	store_env_variables(envp);
	g_data.exit_code = 0;
	path = getcwd(NULL, 0);
	g_data.root_path = ft_strdup(path);
	free(path);
	i = hash_function("HOME") % TABLE_SIZE;
	g_data.home_path = ft_strdup(find_hash_var(g_data.hash_table[i], "HOME"));
}

void	print_startup(void)
{
	int		fd;
	char	buff[1];
	int		index;

	fd = open("./src/assets/startup.txt", O_RDONLY);
	if (fd == -1)
		return ;
	printf("\n");
	index = 0;
	while (read(fd, buff, 1))
	{
		if (index < 74)
			print_color_char(index, buff[0]);
		else
		{
			index = 0;
			print_color_char(index, buff[0]);
		}
		index++;
	}
	printf("\n");
	close(fd);
	return ;
}

void	start_minishell(void)
{
	char				*prompt;
	char				*prompt_input;
	struct sigaction	sint;
	struct sigaction	squit;

	while (1)
	{
		g_data.not_run = 0;
		capture_signals(&sint, &squit);
		prompt = get_prompt();
		prompt_input = readline(prompt);
		free(prompt);
		if (!prompt_input)
			prompt_eof_finish(prompt_input);
		if (prompt_input && *prompt_input)
			add_history(prompt_input);
		execute_line(prompt_input);
	}
}
