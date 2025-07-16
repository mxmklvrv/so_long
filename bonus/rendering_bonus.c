/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:26:50 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/16 13:56:34 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	redraw_player(t_game *game)
{
	int			control;
	mlx_image_t	*image;

	control = 0;
	delete_img(game);
	if (game->dir == 'l')
		image = mlx_texture_to_image(game->mlx, game->textures->player_t_l);
	else
		image = mlx_texture_to_image(game->mlx, game->textures->player_t);
	if (image == NULL)
		annihilate("Failed to redraw player.", game, 1);
	mlx_resize_image(image, PX, PX);
	if (game->dir == 'l')
		game->textures->player_left = image;
	else
		game->textures->player = image;
	control = mlx_image_to_window(game->mlx, image, game->ppos_x * PX,
			game->ppos_y * PX);
	if (control < 0)
		annihilate("Failed to redraw player.", game, 1);
}

void	handle_step(t_game *game)
{
	game->steps++;
	if (game->steps < 0)
		annihilate("https://www.youtube.com/watch?v=GBIIQ0kP15E", game, 1);
	steps_to_screen(game);
}

void	load_map(t_game *game)
{
	int	x;
	int	y;
	int	control;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			control = 0;
			control = mlx_image_to_window(game->mlx, game->textures->floor, x
					* PX, y * PX);
			if (control < 0)
				annihilate("Loading background failed.", game, 1);
			load_rest(game, x, y);
			x++;
		}
		y++;
	}
}

void	load_rest(t_game *game, int x, int y)
{
	int	control;

	control = 0;
	if (game->map[y][x] == 'P')
		control = mlx_image_to_window(game->mlx, game->textures->player, x * PX,
				y * PX);
	else if (game->map[y][x] == 'D')
		control = mlx_image_to_window(game->mlx, game->textures->flower, x * PX,
				y * PX);
	else if (game->map[y][x] == '1')
		control = mlx_image_to_window(game->mlx, game->textures->wall, x * PX, y
				* PX);
	else if (game->map[y][x] == 'E')
		control = mlx_image_to_window(game->mlx, game->textures->exit_closed, x
				* PX, y * PX);
	else if (game->map[y][x] == 'C')
		control = mlx_image_to_window(game->mlx, game->textures->collect, x * PX
				+ PX / 6, y * PX + PX / 6);
	if (control < 0)
		annihilate("Loading failed.", game, 1);
}

void	delete_img(t_game *game)
{
	if (game->textures->player_left)
		mlx_delete_image(game->mlx, game->textures->player_left);
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
}
