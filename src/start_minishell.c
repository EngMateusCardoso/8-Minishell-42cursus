/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:54:15 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/12 17:45:27 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str_prompt(void)
{
	char	*prompt;
	char	*tmp;

	tmp = ft_strjoin(getenv("USER"), "@minislell:");
	prompt = ft_strjoin("\001\033[1;92m\002", tmp);
	free(tmp);
	return (prompt);
}

char	*get_str_path(void)
{
	char	*path;
	char	*home;
	char	*tmp;
	char	*tmp2;

	path = getcwd(NULL, 0);
	home = ft_strdup(getenv("HOME"));
	if (ft_strncmp(path, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", &path[ft_strlen(home)]);
		tmp2 = ft_strjoin("\001\033[1;34m\002", tmp);
		free(path);
		free(home);
		free(tmp);
		return (tmp2);
	}
	else
	{
		tmp = ft_strjoin("\001\033[1;34m\002", path);
		free(path);
		free(home);
		return (tmp);
	}
}

char    *get_prompt(void)
{
    char    *prompt;
    char    *path;
    char    *tmp;
    char    *tmp2;

    prompt = get_str_prompt();
    path = get_str_path();
    tmp = ft_strjoin(prompt, path);
    tmp2 = ft_strjoin(tmp, "\001\033[0m\002$ ");
    free(path);
    free(prompt);
    free(tmp);
    return (tmp2);
}

void    execute_line(char *command)
{
    char    **command_tokens;
    t_cmd   *command_table;

    command_tokens = lexer(command);
    free(command);
    //print_command_tokens(command_tokens);
    if (check_syntax(command_tokens))
    {
        command_table = parser(command_tokens);
        free_command_tokens(command_tokens);
        //print_command_table(command_table);
        g_data.command_table_expanded = expand_command_table(command_table);
        free_command_table(command_table);
        //print_command_table(g_data.command_table_expanded);

        // executar -------------
        if (is_builtin(g_data.command_table_expanded[0].cmd_and_args[0]))
            execute_builtin(g_data.command_table_expanded[0].cmd_and_args);
        // else
        //     execute_executable(command_tokens);
        // executar -------------

        free_command_table(g_data.command_table_expanded);
    }
}

void    start_minishell(void)
{
    char                *prompt;
    char                *prompt_input;
    struct sigaction	sint;
    struct sigaction	squit;

    while (1)
    {
        capture_signals(&sint, &squit);
        prompt = get_prompt();
        prompt_input = readline(prompt);
        free(prompt);
        if (prompt_input && *prompt_input)
		    add_history(prompt_input);
        execute_line(prompt_input);
    }
}
