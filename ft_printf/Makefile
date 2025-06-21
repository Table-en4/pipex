# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molapoug <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:30:53 by molapoug          #+#    #+#              #
#    Updated: 2025/05/21 15:54:24 by molapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs
RM = rm -f

SRC = ft_printf.c ft_printf_px.c \
      ft_printf_unsigned.c ft_utils.c \
      ft_print_str.c

OBJ = $(SRC:.c=.o)

# Color codes
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m # No Color

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)😎🤙Building$(PURPLE) $(NAME)"
	@$(AR) $(NAME) $(OBJ)

%.o: %.c ft_printf.h
	@echo "$(CYAN)🔥Compiling$(GREEN) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(CYAN)🧹Cleaning object files$(NC)"
	@$(RM) $(OBJ)

fclean: clean
	@echo "$(CYAN)🚮Cleaning$(RED) $(NAME)"
	@$(RM) $(NAME)

run: $(SRC)
	@echo "$(GREEN)🔧Building ./ft_printf$(NC)"
	@$(CC) $(CFLAGS) $(SRC) -o ft_printf

re: fclean all

.PHONY: all clean fclean re bonus
