# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molapoug <molapoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:30:53 by molapoug          #+#    #+#              #
#    Updated: 2025/06/26 12:08:51 by molapoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

LIBFT = libft/
FT_PRINTF = ft_printf/

LIBFT_A = $(LIBFT)libft.a
FTPRINTF_A = $(FT_PRINTF)libftprintf.a

RM = rm -f

SRC = pipex.c pipex_utils.c
OBJ = $(SRC:.c=.o)

BONUS_SRC = pipex_bonus.c pipex_utils.c \
			pipex_bonus_utils.c pipex_bonus_utils2.c \
			pipex_bonus_utils3.c
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FTPRINTF_A)
	@echo "$(YELLOW)😎🤙 Linking executable$(PURPLE) $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf -o $(NAME)

bonus: $(BONUS_OBJ) $(LIBFT_A) $(FTPRINTF_A)
	@echo "$(YELLOW)💪 Compiling bonus version$(NC)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -L$(LIBFT) -lft -L$(FT_PRINTF) -lftprintf -o $(NAME)

%.o: %.c pipex.h
	@echo "$(CYAN)🔥 Compiling$(GREEN) $<$(NC)"
	@$(CC) $(CFLAGS) -I$(LIBFT) -I$(FT_PRINTF) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT)

$(FTPRINTF_A):
	@make -C $(FT_PRINTF)

clean:
	@echo "$(CYAN)🧹 Cleaning object files$(NC)"
	@$(RM) $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT) clean
	@make -C $(FT_PRINTF) clean

fclean: clean
	@echo "$(CYAN)🚮 Cleaning$(RED) $(NAME)$(NC)"
	@$(RM) $(NAME)
	@make -C $(LIBFT) fclean
	@make -C $(FT_PRINTF) fclean

re: fclean all

.PHONY: all clean fclean re bonus

