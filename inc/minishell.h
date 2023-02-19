/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:52:56 by matcardo          #+#    #+#             */
/*   Updated: 2023/02/19 12:05:44 by thabeck-         ###   ########.fr       */
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

/******************************************************************************\
 * defines
\******************************************************************************/

# define TABLE_SIZE		50

//prompt styling
# define PROMPT_COLOR	"\001\033[1;92m\002"
# define PATH_COLOR		"\001\033[1;34m\002"
# define RESET_PROMPT	"\001\033[0m\002$ "

//gradient colors
# define COLOR_1		"\e[38;5;82m"
# define COLOR_2		"\e[38;5;83m"
# define COLOR_3		"\e[38;5;84m"
# define COLOR_4		"\e[38;5;85m"
# define COLOR_5		"\e[38;5;86m"
# define COLOR_6		"\e[38;5;87m"
# define RESET_COLOR	"\e[0m"

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
	int				exit_code;
	char			*root_path;
	t_pipes_pids	*pipes_pids;
}					t_data;

typedef struct sigaction	t_sigaction;

extern t_data				g_data;

/******************************************************************************\
 * main functions
\******************************************************************************/

// main.c
void			init_minishell(char **envp);
void			print_startup(void);
void			print_color_char(int index, char c);
void			start_minishell(void);

// signals.c
void			capture_signals(struct sigaction *sint, \
	struct sigaction *squit);
void			handler_signal(int sig);
void			capture_exec_signals(int child_pid);
void			capture_heredoc_signals(int child_pid);

// utils.c
void			error_msg(char *cmd, char *msg, int status);
void			error_handler(char *str1, char *str2, int status, char *cmd);

/******************************************************************************\
 * /execute/
\******************************************************************************/
// get_prompt.c
char			*get_prompt(void);
char			*get_str_prompt(void);
char			*get_str_path(void);

// execute_line.c
void			execute_line(char *command);
int				count_pipes(char **command_tokens);
void			init_pipes_and_pids(int n_pipes);
short int		is_forked(t_cmd *command_table);
void			execute_with_fork(t_cmd *command_table);
void			execute_no_fork(t_cmd *command_table);

// check_syntax.c
short int		check_syntax(char **command_tokens);
short int		syntax_error(char **command_tokens, char *token);

// lexer.c
char			**lexer(char *command);
unsigned int	to_count_tokens(char const *command);
unsigned int	token_size(char const *command, unsigned int i);
unsigned int	quote_token_size(char const *command, unsigned int i, \
	const char quote_type);
char			*put_slices_lexer(char const *command, \
	unsigned int token_index);

// parse.c
t_cmd			*parser(char **command_tokens);
size_t			get_command_table_size(char **command_tokens);
t_cmd			put_complete_cmd(char **command_tokens, \
	unsigned int index_table);
char			**put_cmd_and_args(char **command_tokens, \
	unsigned int start_index, unsigned int end_index);
char			**put_redirections(char **command_tokens, \
	unsigned int start_index, unsigned int end_index);

// parser_utils.c
unsigned int	count_tokens_for(char **command_tokens, \
	unsigned int start_index, unsigned int end_index, char *type);

// execute_with_fork.c
void			execute_with_fork(t_cmd *command_table);
void			close_pipes_in_child(int i);
void			close_pipes_in_parent(void);
void			wait_all_pids(void);

// run_single_command.c
void			run_single_command(char **cmd_and_args);
char			*get_command_path(char *cmd);
void			free_paths(char **paths);

// execute_utils.c
short int		is_redirection(char *token);
unsigned int	redirection_and_pipe_size(char const *command, unsigned int i);
short int		is_redirection_or_pipe(char *token);

/******************************************************************************\
 * /builtin/
\******************************************************************************/
// builtin.c
void			run_builtin(char **command, int isfork);
int				is_builtin(char *command);
char			*clear_quotes(char *var);
int				check_identifier(char *var);
void			identifier_error(char *cmd, char **value);

// cd_builtin.c
void			cd_builtin(char **cmds);
int				cd_exec(char *folder);
void			cd_error(char *folder);
void			change_env(char *key, char *value);

// export_builtin.c
void			export_builtin(char **cmds);
int				has_equal(char *str);
void			print_declarex(void);
void			append_hashtable(char *name);

// unset_builtin.c
void			unset_builtin(char **cmds);
void			delete_from_hashtable(t_list *head, t_list *node, char *key);
void			free_hash_node(t_list *node);

// env_builtin.c
void			env_builtin(void);

// exit_builtin.c
void			exit_builtin(char **cmds);

// echo_builtin.c
void			echo_builtin(char **cmds);
void			print_echo(char **cmds);
void			print_echo_n(char **cmds);

//pwd_builtin.c
void			pwd_builtin(void);

/******************************************************************************\
 * /expander/
\******************************************************************************/
// expander.c
t_cmd			*expand_command_table(t_cmd *cmd);
void			expand_cmd_and_args(char **new_cmds, char **cmds);
void			expand_redirections_and_files(char **new_redir, char **redir);
void			expand_token(char **new_token, char *token, int *j);

// expander_utils.c
int				count_commands(t_cmd *command_table);
int				count_args(char **args);
int				count_wildcards(char *token);

// var_expander.c
void			expand_env_var(char **expand, char *var, int size);
int				expand_var(char **expanded, char *var);
char			*expand_money_sign(char *var);
char			*expand_tilde(char *var);

// var_expander_utils.c
int				is_varkey(char c);
int				can_expand(char *var);
int				single_mark_case(char *token, char **expanded);
int				double_mark_case(char *token, char **expanded);

// wildcard_expander_1.c
void			expand_wildcard(char **new_token, char *token, int *j);
int				has_match(char *str, char *shrunk);
int				match_init_and_end_asterisks(char *str, char *shrunk);
int				match_init_asterisk(char *str, char *shrunk);
int				match_end_asterisk(char *str, char *shrunk);

// wildcard_expander_2.c
int				match_randon_asterisks(char *str, char *shrunk);
int				find_randon_match(char *str, char *fragment, size_t len, \
	int *index);
char			*shrink_asterisks(char *token);

// wildcard_expander_utils.c
int				has_wildcard(char *var);
void			mask_asterisks(char *str);
int				unmask_asterisks(char *str);

/******************************************************************************\
 * /redirection/
\******************************************************************************/
// heredoc.c
void			heredoc(t_cmd *command_table);
void			init_heredoc(char *stop_str, int n_cmd);
void			open_heredoc(char *stop_str, int n_cmd);
int				open_fd_heredoc(char *file, int n_cmd);
void			finish_open_heredoc(int fd);

// set_redirections.c
void			set_redirections(char **redir_and_files, int i);
void			set_redirection_in_pipeline(char *redir, char *file, int i);
int				open_file(char *file, int flags);
int				has_input_redirection(char **redir_and_files);
int				has_output_redirection(char **redir_and_files);

/******************************************************************************\
 * /exit_algorithm/
\******************************************************************************/
// finish_minishell.c
void			finish_minishell(void);
void			finish_free(void);
void			print_closing(void);
void			read_file(char *buff, int fd);

// free_algorithm.c
void			free_command_tokens(char **command_tokens);
void			free_command_table(t_cmd *command_table);
void			free_pipes_and_pids(void);
void			free_hash_table(void);

/******************************************************************************\
 * /hashtable/
\******************************************************************************/
// store_env_variables.c
void			store_env_variables(char **envp);
void			insert_in_hashtable(char *envp);

// hashtable_utils.c
unsigned int	hash_function(char *key);
t_list			*find_hash_node(char *key);
char			*find_hash_var(t_list *head, char *key);

#endif
