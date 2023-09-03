# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 15:03:35 by josorteg          #+#    #+#              #
#    Updated: 2023/09/03 12:25:11 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
HEADER = inc/minishell.h
C_FLAGS = -Wall -Wextra -Werror -MMD -g
RM = rm -f

#------------------------------LIBRARIES---------------------------------------#

SRC_LIBFT = libs/libft/libft.a
MAKE_LIBFT = make -C libs/libft --no-print-directory
READLINE = ./readline/
SRC_READLINE = readline/libreadline.a
SRC_HISTORY = readline/libhistory.a
MAKE_READLINE = make -C readline --no-print-directory

#------------------------------SOURCES-----------------------------------------#
MAIN = main freems prep_exe execution_utils signal executions heredoc errors
ENV = env env2
PARSE = quotes split_tokens expand aux_expand
BUILT = echo envcomand pwd export unset exit newcd

SRC = $(addsuffix .c, $(PARSE)) \
	  $(addsuffix .c, $(ENV)) \
	  $(addsuffix .c, $(MAIN)) \
	  $(addsuffix .c, $(BUILT)) \

F_OBJ = obj/
OBJ = $(addprefix $(F_OBJ), $(SRC:.c=.o))
DEP = $(addprefix $(F_OBJ), $(SRC:.c=.d))

#------------------------------COLORS-----------------------------------------#
BLACK = \033[0;39m
BLUE = \033[0;94m
GREEN = \033[0;92m
MAGENTA = \033[0;95m

#------------------------------EXECUTION-----------------------------------------#
all: dir conf make_libs make_readline $(NAME)

conf:
	@if [ ! -f $(READLINE)config.status ]; then\
		cd $(READLINE) && ./configure; \
	fi

make_libs:
	@echo "$(BLUE)Libft:$(BLACK)"
	@$(MAKE_LIBFT)

make_readline:
	@$(MAKE_READLINE) &> /dev/null

-include ${DEP}

vpath %.c main/:parse/:env/:built-ins

dir:
	@mkdir -p $(F_OBJ)

$(F_OBJ)%.o: %.c
	$(CC) $(C_FLAGS) -I ./inc -c -D READLINE_LIBRARY=1 $< -o $@


$(NAME)::
	@echo "$(GREEN)Minishell:$(BLACK)"

$(NAME):: $(OBJ) ./$(SRC_LIBFT) ./$(SRC_READLINE) ./$(SRC_HISTORY)
	$(CC) $(C_FLAGS) $(^)  -ltermcap -lreadline -o $(NAME)
	@echo "$(GREEN)Everything has been compilated.$(BLACK)"

$(NAME)::
	@echo "$(GREEN)No actions needed.$(BLACK)"

#-L /readline/lib -I /readline/include -L /readline/lib -I /readline/include  -lreadline

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(DEP)
	$(RM) -R obj
	$(MAKE_LIBFT) clean
	$(MAKE_READLINE) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean
	$(MAKE_READLINE) clean
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"

re: fclean all
