/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:23:01 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/10 12:23:13 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
    if (game->dying == true)
        return;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		game->dir = 'r';
		action(game, 'r');
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		game->dir = 'l';
		action(game, 'l');
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		action(game, 'u');
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		action(game, 'd');
}

void	action(t_game *game, char dir)
{
	if ((dir == 'r') && (game->map[game->ppos_y][game->ppos_x + 1] != '1'))
	{
		game->ppos_x += 1;
		redraw_player(game);
		handle_step(game);
	}
	else if ((dir == 'l') && (game->map[game->ppos_y][game->ppos_x - 1] != '1'))
	{
		game->ppos_x -= 1;
		redraw_player(game);
		handle_step(game);
	}
	else if ((dir == 'u') && (game->map[game->ppos_y - 1][game->ppos_x] != '1'))
	{
		game->ppos_y -= 1;
		check_face_side(game);
		handle_step(game);
	}
	else if ((dir == 'd') && (game->map[game->ppos_y + 1][game->ppos_x] != '1'))
	{
		game->ppos_y += 1;
		check_face_side(game);
		handle_step(game);
	}
	bonus_status(game);
}

void	bonus_status(t_game *game)
{
	int	control;

	control = 0;
	if (game->map[game->ppos_y][game->ppos_x] == 'D')
	{
        game->dying = true;
        game->death_frame = 0;
		
	}
	if (game->map[game->ppos_y][game->ppos_x] == 'E')
	{
		if (game->loot == game->looted)
		{
			ft_printf("\033[32mAll eaten in %d steps!\033[0m", game->steps);
			annihilate("\n", game, 0);
		}
		else
			ft_printf("\033[33mStill some food to eat.\n\033[0m");
	}
	game_status(game);
}

void	game_status(t_game *game)
{
	int	control;

	control = 0;
	if (game->map[game->ppos_y][game->ppos_x] == 'C')
	{
		control = mlx_image_to_window(game->mlx, game->textures->floor,
				game->ppos_x * PX, game->ppos_y * PX);
		if (control < 0)
			annihilate("Failed to redraw floor.", game, 1);
		check_face_side(game);
		ft_printf("\033[1;33mFood eaten\n\033[0m");
		game->looted++;
		game->map[game->ppos_y][game->ppos_x] = '0';
	}
	if (game->loot == game->looted)
	{
		mlx_delete_image(game->mlx, game->textures->exit_closed);
		control = mlx_image_to_window(game->mlx, game->textures->exit,
				game->epos_x * PX, game->epos_y * PX);
		if (control < 0)
			annihilate("Failed to redraw exit.", game, 1);
	}
}
void	check_face_side(t_game *game)
{
	mlx_texture_t	*before_food;
	mlx_texture_t	*before_food_left;

	if (game->map[game->ppos_y][game->ppos_x] == 'C')
	{
		before_food = game->textures->player_t;
		before_food_left = game->textures->player_t_l;
		game->textures->player_t = game->textures->player_ta;
		game->textures->player_t_l = game->textures->player_ta_l;
		redraw_player(game);
		game->textures->player_t = before_food;
		game->textures->player_t_l = before_food_left;
	}
	else
		redraw_player(game);
}
