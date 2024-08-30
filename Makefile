# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndo-vale <ndo-vale@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 14:30:34 by ndo-vale          #+#    #+#              #
#    Updated: 2024/08/30 12:56:52 by ndo-vale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
IFLAGS		= -I./ 
LFLAGS		= -lm -lXext -lX11 -O3
RM			= rm -rf

PREP_DIRS	= prep
SRC_DIR		= src/
OBJ_DIR		= obj/

SRCS		= $(addprefix $(SRC_DIR), main.c tuple_factory.c tuple_operations.c\
					helpers.c clean_exit.c matrix_factory.c matrix_operations.c)
OBJS		= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p obj

$(LIBFT):
	@echo "Compiling LIBFT..."
	make -s -C $(LIBFT_DIR)

$(MLX):
	@echo "compiling MLX..."
	make -s -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(IFLAGS) $(LFLAGS) $(LIBFT) $(MLX)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	make -s clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re