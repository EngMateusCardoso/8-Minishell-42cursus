/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:34:38 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/21 14:56:16 by thabeck-         ###   ########.fr       */
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
	print_startup();
	g_data.envp = envp;
	store_env_variables(envp);
	g_data.exit_code = 0;
	g_data.root_path = getcwd(NULL, 0);
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

void	print_color_char(int index, char c)
{
	if (index < 12)
		printf("%s%c", COLOR_1, c);
	else if (index < 24)
		printf("%s%c", COLOR_2, c);
	else if (index < 36)
		printf("%s%c", COLOR_3, c);
	else if (index < 48)
		printf("%s%c", COLOR_4, c);
	else if (index < 60)
		printf("%s%c", COLOR_5, c);
	else
		printf("%s%c%s", COLOR_6, c, RESET_COLOR);
}

void	start_minishell(void)
{
	char				*prompt;
	char				*prompt_input;
	struct sigaction	sint;
	struct sigaction	squit;

	while (1)
	{
		capture_signals(&sint, &squit);
		prompt = get_prompt();
		prompt_input = readline(prompt);
		free(prompt);
		if (!prompt_input)
		{
			print_closing();
			free_hash_table();
			free(g_data.root_path);
			rl_clear_history();
			free(prompt_input);
			exit(127);
		}
		if (prompt_input && *prompt_input)
			add_history(prompt_input);
		execute_line(prompt_input);
	}
}
