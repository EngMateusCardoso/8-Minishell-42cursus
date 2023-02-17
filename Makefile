# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matcardo <matcardo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 02:09:58 by matcardo          #+#    #+#              #
#    Updated: 2023/02/16 14:05:50 by matcardo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= 	main.c								\
					lexer.c								\
					parser.c								\
					hashtable.c							\
					signals.c								\
					utils.c								\
					start_minishell.c						\
					run_single_command.c					\
					finish_minishell.c					\
					free_algorithm.c						\
					check_syntax.c						\
					debug_functions.c						\
					builtins/builtin.c					\
					builtins/cd_builtin.c					\
					builtins/env_builtin.c				\
					builtins/exit_builtin.c				\
					builtins/export_builtin.c				\
					builtins/unset_builtin.c				\
					builtins/echo_builtin.c				\
					builtins/pwd_builtin.c				\
					expander/expander.c					\
					expander/expander_utils.c				\
					expander/var_expander.c				\
					expander/var_expander_utils.c			\
					expander/wildcard_expander_1.c		\
					expander/wildcard_expander_2.c		\
					expander/wildcard_expander_utils.c	\

OBJS			= ${SRCS:%.c=%.o}
HEADER			= src/minishell.h
OBJS_DIR		= objs/

RM				= rm -fr
CC				= gcc
FLAGS			= -Wall -Wextra -Werror -g

LEAKS 			= valgrind
LEAKS_FILE		= valgrind-out.txt
LF 				= --suppressions=readline.supp \
				--leak-check=full \
				--track-origins=yes \
				--show-leak-kinds=all \
				--log-file=$(LEAKS_FILE)

LIBFT			= ./libraries/libft/
LIBS			= -L $(LIBFT) -lft  -lreadline

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all:		$(NAME)

$(NAME):	$(OBJS_DIR) $(addprefix $(OBJS_DIR),$(OBJS)) $(LIBFT)
	@printf "\r$(CY)Generating minishell executable...                              $(RC)\n"
	@$(CC) $(addprefix $(OBJS_DIR),$(OBJS)) -o $(NAME) $(LIBS)
	@printf "$(GR)minishell is Ready!$(RC)\n"

$(OBJS_DIR):
	@mkdir $(OBJS_DIR) $(OBJS_DIR)/builtins $(OBJS_DIR)/expander

objs/%.o:	src/%.c
	@printf "\r$(CY)Generating object "$@
	@$(CC) -c -o $@ $< $(LIBS)
	@printf "$(RC)                              "

$(LIBFT):
	@printf "\n$(CY)Generating libft...$(RC)\n"
	@make bonus -C ./libraries/libft
	@printf "$(GR)libft ready!$(RC)"

norm:
	norminette ${SRCS} ${HEADER}

leaks:
	$(LEAKS) $(LF) ./$(NAME)

clean:
	@$(RM) $(OBJS_DIR)
	@printf "$(RE)minishell objects removed!$(RC)\n"

fclean:		clean
	@$(RM) $(NAME)
	@printf "$(RE)minishell removed!$(RC)\n"

re:			fclean all

.PHONY:		all clean fclean re
