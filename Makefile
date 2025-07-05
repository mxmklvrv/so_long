# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:36:29 by mklevero          #+#    #+#              #
#    Updated: 2025/07/05 16:11:25 by mklevero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc -g
CFLAGS = -Wall -Wextra -Werror

MLX42_DIR = ./MLX42
MLX42 = $(MLX42_DIR)/build/libmlx42.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj/
SRC_DIR = src/

HEADERS = -I ./include -I $(MLX42_DIR)/include -I $(LIBFT_DIR)
MLX_LIBS = $(MLX42) -ldl -lglfw -pthread -lm

SRCS = main.c error.c map_validation.c map_validation_2.c helpers.c \
path_validation.c loading_img.c

OBJ = $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
.SECONDARY: ${OBJ}

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(MLX42): $(MLX42_DIR)
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build
	@make -C $(MLX42_DIR)/build -j4

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJ) $(LIBFT) $(MLX42)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIBS) -o $(NAME)
clean:
		rm -rf $(OBJ_DIR)
		make clean -C $(LIBFT_DIR)
fclean: clean
		rm -f $(NAME) $(LIBFT)
		rm -rf $(MLX42_DIR)/build
re: fclean all

.PHONY: all clean fclean re 
