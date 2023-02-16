/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:52:56 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/16 11:03:50 by thabeck-         ###   ########.fr       */
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

typedef struct sigaction	t_sigaction;

/******************************************************************************\
 * global var
\******************************************************************************/

extern t_data	g_data;

void		store_env_variables(char **envp);
void		start_minishell(void);
void		free_hash_table(void);
void		finish_minishell(void);
void		print_command_tokens(char **command_tokens);
void		free_command_tokens(char **command_tokens);
char		**lexer(char *command);
t_cmd		*parser(char **command_tokens);
void		print_command_table(t_cmd *command_table);
void		free_command_table(t_cmd *command_table);
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
 * /builtin/
\******************************************************************************/
// builtin.c
void	execute_builtin(char **command, int isfork);
int		is_builtin(char *command);
char	*clear_quotes(char *var);
int		check_identifier(char *var);
void	identifier_error(char *cmd, char **value);

// cd_builtin.c
void	cd_builtin(char **cmds);
int		cd_exec(char *folder);
void	cd_error(char *folder);
void	change_env(char *key, char *value);

// export_builtin.c
void	export_builtin(char **cmds);
int		has_equal(char *str);
void	print_declarex(void);
void	append_hashtable(char *name);

// unset_builtin.c
void	unset_builtin(char **cmds);
void	delete_from_hashtable(t_list *head, t_list *node, char *key);
void	free_hash_node(t_list *node);

// env_builtin.c
void	env_builtin(void);

// exit_builtin.c
void	exit_builtin(char **cmds);

// echo_builtin.c
void	echo_builtin(char **cmds);
void	print_echo(char **cmds);
void	print_echo_n(char **cmds);

//pwd_builtin.c
void	pwd_builtin(void);

/******************************************************************************\
 * /expander/
\******************************************************************************/
// expander.c
t_cmd	*expand_command_table(t_cmd *cmd);
void	expand_cmd_and_args(char **new_cmds, char **cmds);
void	expand_redirections_and_files(char **new_redir, char **redir);
void	expand_token(char **new_token, char *token, int *j);

// expander_utils.c
int		count_commands(t_cmd *command_table);
int		count_args(char **args);
int		count_wildcards(char *token);

// var_expander.c
void	expand_env_var(char **expand, char *var, int size);
int		expand_var(char **expanded, char *var);
char	*expand_money_sign(char *var);
char	*expand_tilde(char *var);

// var_expander_utils.c
int		is_varkey(char c);
int		can_expand(char *var);
int		single_mark_case(char *token, char **expanded);
int		double_mark_case(char *token, char **expanded);

// wildcard_expander_1.c
void	expand_wildcard(char **new_token, char *token, int *j);
int		has_match(char *str, char *shrunk);
int		match_init_and_end_asterisks(char *str, char *shrunk);
int		match_init_asterisk(char *str, char *shrunk);
int		match_end_asterisk(char *str, char *shrunk);

// wildcard_expander_2.c
int		match_randon_asterisks(char *str, char *shrunk);
int		find_randon_match(char *str, char *fragment, size_t len, int *index);
char	*shrink_asterisks(char *token);

// wildcard_expander_utils.c
int		has_wildcard(char *var);
void	mask_asterisks(char *str);
int		unmask_asterisks(char *str);

#endif
