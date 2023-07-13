# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: josorteg <josorteg@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 15:03:35 by josorteg          #+#    #+#              #
#    Updated: 2023/07/13 09:45:44 by josorteg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = inc/minishell.h
C_FLAGS = -Wall -Wextra -Werror -MMD -g
RM = rm -f

#------------------------------LIBRARIES---------------------------------------#

SRC_LIBFT = libs/libft/libft.a
MAKE_LIBFT = make -C libs/libft --no-print-directory
SRC_READLINE = readline/libreadline.a
SRC_HISTORY = readline/libhistory.a
MAKE_READLINE = make -C readline --no-print-directory

#------------------------------SOURCES-----------------------------------------#
MAIN = main freems prep_exe
ENV = env
PARSE = quotes split_tokens
BUILT = echo envcomand pwd cd export

SRC = $(addsuffix .c, $(PARSE)) \
	  $(addsuffix .c, $(ENV)) \
	  $(addsuffix .c, $(MAIN)) \
	  $(addsuffix .c, $(BUILT)) \

F_OBJ = obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

all: dir make_libs make_readline $(NAME)

make_libs:
	@$(MAKE_LIBFT)

make_readline:
	@$(MAKE_READLINE)

-include ${DEP}

vpath %.c main/:parse/:env/:built-ins

dir:
	@mkdir -p $(F_OBJ)

$(F_OBJ)%.o: %.c
	$(CC) $(C_FLAGS) -I ./inc -c -D READLINE_LIBRARY=1 $< -o $@

$(NAME):: $(OBJ) ./$(SRC_LIBFT) ./$(SRC_READLINE) ./$(SRC_HISTORY)
	$(CC) $(C_FLAGS) $(^) -ltermcap -o $(NAME)
	@echo "$(BLUE)Everything has been compilated.$(BLACK)"

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) -R obj
	$(MAKE_LIBFT) clean
	$(MAKE_READLINE) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"

re: fclean all
.SILENT:
