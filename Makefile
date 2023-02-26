# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 02:09:58 by matcardo          #+#    #+#              #
#    Updated: 2023/02/26 17:44:04 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= 	main.c								\
					utils.c								\
					debug_functions.c					\
					execute/get_prompt.c				\
					execute/execute_line.c				\
					execute/check_syntax.c				\
					execute/lexer.c						\
					execute/parser.c					\
					execute/parser_utils.c				\
					execute/execute_with_fork.c			\
					execute/execute_with_fork_utils.c	\
					execute/run_native_command.c		\
					execute/execute_utils.c				\
					hashtable/store_env_variables.c		\
					hashtable/hashtable_utils.c			\
					builtins/builtin.c					\
					builtins/cd_builtin.c				\
					builtins/env_builtin.c				\
					builtins/exit_builtin.c				\
					builtins/export_builtin.c			\
					builtins/unset_builtin.c			\
					builtins/echo_builtin.c				\
					builtins/pwd_builtin.c				\
					expander/expander.c					\
					expander/expander_utils.c			\
					expander/var_expander.c				\
					expander/var_expander_utils.c		\
					expander/wildcard_expander_1.c		\
					expander/wildcard_expander_2.c		\
					expander/wildcard_expander_utils.c	\
					redirections/heredoc.c				\
					redirections/heredoc_utils.c		\
					redirections/set_redirections.c		\
					exit_algorithm/finish_minishell.c	\
					exit_algorithm/free_algorithm.c		\
					signals/signals.c					\
					signals/signals_handler.c			\

OBJS			= ${SRCS:%.c=%.o}
HEADER			= ./inc/minishell.h
OBJS_DIR		= objs/

RM				= rm -fr
CC				= clang
FLAGS			= -Wall -Wextra -Werror

LEAKS 			= valgrind
LEAKS_FILE		= valgrind-out.txt
LF				= --suppressions=readline.supp \
				--leak-check=full \
				--track-origins=yes \
				--show-leak-kinds=all \
				--log-file=$(LEAKS_FILE)

LIBFT			= ./libraries/libft/
LIBS			= -L $(LIBFT) -lft  -lreadline
LIBFTA			= $(LIBFT)libft.a

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all:		$(NAME)

$(NAME):	 $(LIBFTA) $(OBJS_DIR) $(addprefix $(OBJS_DIR),$(OBJS))
	@printf "\r$(CY)Generating minishell executable...                                 $(RC)\n"
	@$(CC) $(FLAGS) $(addprefix $(OBJS_DIR),$(OBJS)) -o $(NAME) $(LIBS)
	@printf "$(GR)minishell is Ready!$(RC)\n"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR) $(OBJS_DIR)/builtins $(OBJS_DIR)/execute $(OBJS_DIR)/exit_algorithm $(OBJS_DIR)/expander $(OBJS_DIR)/hashtable $(OBJS_DIR)/redirections $(OBJS_DIR)/signals

objs/%.o:	src/%.c
	@printf "\r$(CY)Generating object "$@
	@$(CC) $(FLAGS) -c -o $@ $<
	@printf "$(RC)                              "

$(LIBFTA):
	@printf "$(CY)Generating libft...$(RC)\n"
	@make bonus -C ./libraries/libft
	@printf "$(GR)libft ready!$(RC)"

norm:
	@norminette ./src/ ./inc/

leaks:		$(NAME)
	$(LEAKS) $(LF) ./$(NAME)

clean:
	@$(RM) $(OBJS_DIR) $(LEAKS_FILE)
	@make clean -C ./libraries/libft
	@printf "$(RE)minishell objects removed!$(RC)\n"

fclean:		clean
	@$(RM) $(NAME)
	@make fclean -C ./libraries/libft
	@printf "$(RE)minishell removed!$(RC)\n"

re:			fclean all

.PHONY:		all clean fclean re norm
