/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:52:15 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 16:07:45 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_exit(t_textures *textures, t_game *game)
{
	mlx_texture_t	*exit;

	exit = mlx_load_png("./img/vihod3.png");
	if (exit == NULL)
		annihilate("Loading exit failed", game, 1);
	textures->exit = mlx_texture_to_image(game->mlx, exit);
	if (textures->exit == NULL)
	{
		mlx_delete_texture(exit);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->exit, PX, PX);
	mlx_delete_texture(exit);
}

void	load_loot(t_textures *textures, t_game *game)
{
	mlx_texture_t	*loot;

	loot = mlx_load_png("./img/obj3.png");
	if (loot == NULL)
		annihilate("Loading collectable failed.", game, 1);
	textures->collect = mlx_texture_to_image(game->mlx, loot);
	if (textures->collect == NULL)
	{
		mlx_delete_texture(loot);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->collect, (PX * 3) / 4, (PX * 3) / 4);
	mlx_delete_texture(loot);
}

void	load_walls(t_textures *textures, t_game *game)
{
	mlx_texture_t	*wall;

	wall = mlx_load_png("./img/stone.png");
	if (wall == NULL)
		annihilate("Loading wall failed", game, 1);
	textures->wall = mlx_texture_to_image(game->mlx, wall);
	if (textures->wall == NULL)
	{
		mlx_delete_texture(wall);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->wall, PX, PX);
	mlx_delete_texture(wall);
}

void	load_floor(t_textures *textures, t_game *game)
{
	mlx_texture_t	*floor;

	floor = mlx_load_png("./img/pol2.png");
	if (floor == NULL)
		annihilate("Loading floor failed.", game, 1);
	textures->floor = mlx_texture_to_image(game->mlx, floor);
	if (textures->floor == NULL)
	{
		mlx_delete_texture(floor);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->floor, PX, PX);
	mlx_delete_texture(floor);
}

void	load_player(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player;

	player = mlx_load_png("./img/demon.png");
	if (player == NULL)
		annihilate("Loading player failed.", game, 1);
	textures->player_t = player;
	textures->player = mlx_texture_to_image(game->mlx, player);
	if (textures->player == NULL)
		annihilate("Loading texture to img failed.", game, 1);
	mlx_resize_image(textures->player, PX, PX);
}
