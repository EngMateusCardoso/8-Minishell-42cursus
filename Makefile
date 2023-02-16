# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thabeck- <thabeck-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 02:09:58 by matcardo          #+#    #+#              #
#    Updated: 2023/02/15 21:07:45 by thabeck-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SRCS			= 	./src/main.c					\
					./src/lexer.c					\
					./src/parser.c					\
					./src/hashtable.c				\
					./src/signals.c					\
					./src/utils.c					\
					./src/start_minishell.c			\
					./src/run_single_command.c		\
					./src/expand_command_table.c	\
					./src/finish_minishell.c		\
					./src/free_algorithm.c			\
					./src/check_syntax.c			\
					./src/debug_functions.c			\
					./src/builtins/builtin.c		\
					./src/builtins/cd_builtin.c		\
					./src/builtins/env_builtin.c	\
					./src/builtins/exit_builtin.c	\
					./src/builtins/export_builtin.c	\
					./src/builtins/unset_builtin.c	\
					./src/builtins/echo_builtin.c	\
					./src/builtins/pwd_builtin.c	\

OBJS			= ${SRCS:src/%.c=objs/%.o}
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

LIBFT			= ./libraries/libft/libft.a
LIBS			= $(LIBFT) -lreadline

GR				= \033[32;1m
RE				= \033[31;1m
CY				= \033[36;1m
RC				= \033[0m

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
			@printf "\n$(CY)Generating minishell executable...$(RC)\n"
			@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBS)
			@printf "$(GR)minishell is Ready!$(RC)\n\n"

$(OBJS_DIR):
			@mkdir $(OBJS_DIR)

objs/%.o: src/%.c
			@printf "\n$(CY)Generating object...$(RC)\n"
			@${CC} ${FLAGS} -c $< -o ${<:src/%.c=objs/%.o}
			@printf "$(GR)Object ready!$(RC)"

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
			@printf "\n$(RE)minishell objects removed!$(RC)\n"

fclean:		clean
			@$(RM) $(NAME)
			@printf "$(RE)minishell removed!$(RC)\n\n"

re:			fclean all

.PHONY:		all clean fclean re
