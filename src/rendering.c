/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:26:50 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/07 19:27:03 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	redraw_player(t_game *game, int decider)
{
	int	control;

	control = 0;
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	game->textures->player = mlx_texture_to_image(game->mlx,
			game->textures->player_t);
	if (game->textures->player == NULL)
		annihilate("Failed to redraw player", game, 1);
	mlx_resize_image(game->textures->player, PX, PX);
	control = mlx_image_to_window(game->mlx, game->textures->player,
			game->ppos_x * PX, game->ppos_y * PX);
	if (control < 0)
		annihilate("Failed to redraw player.", game, 1);
	if (decider == 0)
	{
		game->steps++;
		ft_printf("Number of steps: %d\n", game->steps);
	}
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
	else if (game->map[y][x] == '1')
		control = mlx_image_to_window(game->mlx, game->textures->wall, x * PX, y
				* PX);
	else if (game->map[y][x] == 'E')
		control = mlx_image_to_window(game->mlx, game->textures->exit, x * PX, y
				* PX);
	else if (game->map[y][x] == 'C')
		control = mlx_image_to_window(game->mlx, game->textures->collect, x * PX
				+ PX / 6, y * PX + PX / 6);
	if (control < 0)
		annihilate("Loading failed.", game, 1);
}
