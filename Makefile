# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:36:29 by mklevero          #+#    #+#              #
#    Updated: 2025/07/16 14:04:27 by mklevero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX42_DIR = ./MLX42
MLX42 = $(MLX42_DIR)/build/libmlx42.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj/
SRC_DIR = src/

SRC_BONUS_DIR = bonus/
OBJ_BONUS_DIR = obj_bonus/

HDR = include/so_long.h libft/libft.h
HEADERS = -I ./include -I $(MLX42_DIR)/include -I $(LIBFT_DIR)
MLX_LIBS = $(MLX42) -ldl -lglfw -pthread -lm

SRCS = main.c error.c map_validation.c map_validation_2.c helpers.c \
path_validation.c uploading_img.c gameplay.c rendering.c annihilate.c 

BONUS_SRCS = annihilate_bonus.c error_bonus.c gameplay_bonus.c \
helpers_bonus.c main_bonus.c map_validation_2_bonus.c \
map_validation_bonus.c path_validation_bonus.c rendering_bonus.c \
uploading_img_bonus.c uploading_img_bonus_2.c uploading_img_bonus_3.c \
death_animation.c

OBJ = $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
.SECONDARY: $(OBJ)

OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR),$(BONUS_SRCS:.c=.o))
.SECONDARY: $(OBJ_BONUS)

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

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJ) $(LIBFT) $(MLX42) $(HDR)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIBS) -o $(NAME)
bonus: .bonus

.bonus: $(OBJ_BONUS) $(LIBFT) $(MLX42)
		$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) $(MLX_LIBS) -o $(NAME_BONUS)
		@touch .bonus
clean:
		rm -rf $(OBJ_DIR)
		rm -rf $(OBJ_BONUS_DIR)
		rm -f .bonus
		make clean -C $(LIBFT_DIR)
fclean: clean
		rm -f $(NAME) $(NAME_BONUS) $(LIBFT)
		rm -rf $(MLX42_DIR)/build

re: fclean all

.PHONY: all clean fclean re 
