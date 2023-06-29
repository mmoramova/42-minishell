# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 18:48:29 by josorteg          #+#    #+#              #
#    Updated: 2023/06/29 19:57:34 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = inc/minishell.h
C_FLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f
SRC_LIBFT = libs/libft/libft.a
MAKE_LIBFT = make -C libs/libft --no-print-directory
SRC_READLINE = readline/libreadline.a
SRC_HISTORY = readline/libhistory.a
MAKE_READLINE = make -C readline --no-print-directory

# Colors
BLACK = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = main env split_tokens
SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

all: make_libs make_readline $(NAME)

make_libs:
	@$(MAKE_LIBFT)

make_readline:
	@$(MAKE_READLINE)

-include ${DEP}

%.o: %.c
	$(CC) $(C_FLAGS) -c -D READLINE_LIBRARY=1 $< -o $@

$(NAME):: $(OBJ) ./$(SRC_LIBFT) ./$(SRC_READLINE) ./$(SRC_HISTORY)
	$(CC) $(C_FLAGS) $(^) -ltermcap -o $(NAME)
	@echo "$(BLUE)Everything has been compilated.$(BLACK)"

$(NAME)::
	@echo "$(BLUE)No actions needed.$(BLACK)"

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(DEP)
	$(MAKE_LIBFT) clean
	$(MAKE_READLINE) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean
	$(MAKE_READLINE) fclean
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"

re: fclean all
