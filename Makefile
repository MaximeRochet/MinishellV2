# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 16:16:40 by cerisemasse       #+#    #+#              #
#    Updated: 2021/11/09 16:09:48 by cmasse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ERASE		=	\033[2K\r
GREY		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
PINK		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
BOLD		=	\033[1m
UNDER		=	\033[4m
SUR			=	\033[7m
END			=	\033[0m

NAME = minishell

SRCS_NAME = liste.c minishell.c \
			print_struct.c \
			recup_prompt.c execution.c execution_deux.c execution_trois.c \
			fonction.c fonction_deux.c  fonction_trois.c space.c signal.c \
			free.c heredoc.c fonction_exit.c fonction_exit_deux.c \
			$(SRCS_UTILS) $(SRCS_PARSING)

SRCS_UTILS = $(addprefix $(UTILS_PATH)/, utils.c utils_2.c)
SRCS_PARSING = $(addprefix $(PARSING_PATH)/, parsing_init.c parsing_var.c parsing_pipe.c parsing_cmd.c parsing_redirection.c)

LIB_NAME = ./minishell.h 

RL_FLAG     = -lreadline -L /Users/$(shell whoami)/.brew/opt/readline/lib
RL_OBJ      = -I/Users/$(shell whoami)/.brew/opt/readline/include

SRCS_PATH = srcs
UTILS_PATH = utils
PARSING_PATH = parsing
LIB_PATH = ./includes
OBJS_PATH = .objs

OBJS_NAME = ${SRCS_NAME:.c=.o}

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

HEADER		= minishell.h
			
RM		=	rm -f
CC		=	gcc 
CFLAGS	=	-Wall -Werror -Wextra
LIB_FT	= libft/libft.a
#FSAN	=	-g -fsanitize=address

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(LIB) $(LIB_FT)
			@mkdir -p $(OBJS_PATH)
			@mkdir -p $(OBJS_PATH)/utils
			@mkdir -p $(OBJS_PATH)/parsing
			@$(CC) $(CFLAGS) $(RL_OBJ) -c $< -o $@ -I $(LIB_PATH)
			
all		:	librairies
			@$(MAKE) $(NAME)

$(NAME):	${OBJS}
			@$(CC) ${CFLAGS} ${OBJS} libft/*.o -o ${NAME} ${FSAN} -Llibft -lft $(RL_FLAG)
			@echo "\x1b[32m 🍒 Compilation effectuée 🍒\x1b[0m" 

librairies:
			@make -C libft
			
clean:
			@${RM} -rf  ${OBJS_PATH}
			@make clean -C libft
			
fclean:		clean
			@${RM} ${NAME}
			@make fclean -C libft
			@echo "\x1b[35m 😈 Tout a été supprimé 😈 \x1b[0m"

re:			fclean all 
