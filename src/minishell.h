/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:52:56 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/14 21:39:12 by thabeck-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************\
 * includes
\******************************************************************************/

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libraries/libft/libft.h"

# define TABLE_SIZE 50

/******************************************************************************\
 * structs
\******************************************************************************/

typedef struct s_env_var
{
	char		*key;
	char		*value;
}				t_env_var;

typedef struct s_cmd
{
	char		**cmd_and_args;
	char		**redirections_and_files;
}				t_cmd;

typedef struct s_pipes_pids
{
	int			**pipes;
	pid_t		*pids;
	int			total_cmd;
}				t_pipes_pids;

typedef struct s_data
{
	t_list			*(hash_table[TABLE_SIZE]);
	char			**envp;
	t_cmd			*command_table_expanded;
	int					exit_code;
	char			*root_path;
	t_pipes_pids	*pipes_pids;
}					t_data;

/******************************************************************************\
 * global var
\******************************************************************************/

extern t_data	g_data;

void		store_env_variables(char **envp);
void		start_minishell(void);
int			is_builtin(char *command);
void		execute_builtin(char **command, int isfork);
void		free_hash_table(void);
void		finish_minishell(void);
void		print_command_tokens(char **command_tokens);
void		free_command_tokens(char **command_tokens);
char		**lexer(char *command);
t_cmd		*parser(char **command_tokens);
void		print_command_table(t_cmd *command_table);
void		free_command_table(t_cmd *command_table);
t_cmd		*expand_command_table(t_cmd *command_table);
short int	check_syntax(char **command_tokens);
short int	is_redirection(char *token);
void		print_color_char(int idx, char c);
char		*get_prompt(void);
void		execute_line(char *command);
void		capture_signals(struct sigaction *sint, struct sigaction *squit);
char		*find_hash_var(t_list *head, char *key);
t_list		*find_hash_node(char *key);
unsigned int hash_function(char *key);
void		free_pipes_and_pids(void);
void		run_single_command(char **cmd_and_args);
void		error_handler(char *str1, char *str2, int status, char *cmd);
void		error_msg(char *cmd, char *msg, int status);
void		insert_in_hashtable(char *envp);

/******************************************************************************\
 * builtin.c
\******************************************************************************/
void	execute_builtin(char **command, int isfork);
int		is_builtin(char *command);
char	*clear_quotes(char *var);
int		check_identifier(char *var);
void	identifier_error(char *cmd, char **value);

/******************************************************************************\
 * cd_builtin.c
\******************************************************************************/
void	cd_builtin(char **cmds);
int		cd_exec(char *folder);
void	cd_error(char *folder);
void	change_env(char *key, char *value);

/******************************************************************************\
 * export_builtin.c
\******************************************************************************/
void	export_builtin(char **cmds);
int		has_equal(char *str);
void	print_declarex(void);
void	append_hashtable(char *name);

/******************************************************************************\
 * unset_builtin.c
\******************************************************************************/
void	unset_builtin(char **cmds);
void	delete_from_hashtable(t_list *head, t_list *node, char *key);
void	free_hash_node(t_list *node);

/******************************************************************************\
 * env_builtin.c
\******************************************************************************/
void	env_builtin(void);

/******************************************************************************\
 * exit_builtin.c
\******************************************************************************/
void	exit_builtin(char **cmds);

#endif
