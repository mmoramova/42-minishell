# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/03 19:27:46 by mmoramov          #+#    #+#              #
#    Updated: 2023/04/26 17:32:29 by mmoramov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
C_FLAGS = -Wall -Wextra -Werror
RM = rm -f

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

SRC_FILES = ft_isalpha   ft_toupper    ft_isdigit    ft_tolower \
			ft_isalnum   ft_strchr     ft_isascii    ft_strrchr \
			ft_isprint   ft_strncmp    ft_strlen     ft_memchr  \
			ft_memset    ft_memcmp     ft_bzero      ft_strnstr \
			ft_memcpy    ft_atoi       ft_memmove    ft_calloc  \
			ft_strlcpy   ft_strdup     ft_strlcat    ft_substr  \
			ft_strjoin   ft_strtrim    ft_split      ft_itoa    \
			ft_strmapi   ft_striteri   ft_putchar_fd            \
			ft_putstr_fd ft_putendl_fd ft_putnbr_fd				\
			get_next_line get_next_line_utils

SRC_FILES_BONUS = ft_lstnew ft_lstadd_front ft_lstsize   \
				  ft_lstlast ft_lstadd_back ft_lstdelone \
				  ft_lstclear ft_lstiter ft_lstmap

SRC = $(addsuffix .c, $(SRC_FILES))
SRC_BONUS = $(addsuffix .c, $(SRC_FILES_BONUS))
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

INCLUDE = -I ./

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

$(NAME):: $(OBJ) $(HEADER)
	ar -rcs $(NAME) $(OBJ)
	@echo "$(BLUE)Everything has been compilated.$(BLACK)"

$(NAME)::
	@echo "$(BLUE)No actions needed.$(BLACK)"

bonus:: $(OBJ) $(OBJ_BONUS) $(HEADER)
	touch $@
	ar -rcs $(NAME) $(OBJ) $(OBJ_BONUS)
	@echo "$(GREEN)Everything has been compilated.$(BLACK)"

bonus::
	@echo "$(GREEN)No actions needed.$(BLACK)"

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJ) $(OBJ_BONUS) 
fclean: clean
	$(RM) $(NAME) bonus
	@echo "$(MAGENTA)Everything has been cleaned.$(BLACK)"
	
re: fclean all

