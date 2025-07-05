/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:52:15 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 12:11:57 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_exit(t_textures *textures, t_game *game)
{
	mlx_texture_t	*exit;

	exit = mlx_load_png("./img/vihod2.png");
	if (exit == NULL)
		error_and_destroy("Loading exit failed", game);
	textures->exit = mlx_texture_to_image(game->mlx, exit);
	if (textures->exit == NULL)
	{
		mlx_delete_texture(exit);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->exit, PX, PX);
	mlx_delete_texture(exit);
}

void	load_loot(t_textures *textures, t_game *game)
{
	mlx_texture_t	*loot;

	loot = mlx_load_png("./img/jazo.png");
	if (loot == NULL)
		error_and_destroy("Loading collectable failed", game);
	textures->collect = mlx_texture_to_image(game->mlx, loot);
	if (textures->collect == NULL)
	{
		mlx_delete_texture(loot);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->collect, PX, PX);
	mlx_delete_texture(loot);
}

void	load_player(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player;

	player = mlx_load_png("./img/demon.png");
	if (player == NULL)
		error_and_destroy("Loading player failed", game);
	textures->player = mlx_texture_to_image(game->mlx, player);
	if (textures->player == NULL)
	{
		mlx_delete_texture(player);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->player, PX, PX);
	mlx_delete_texture(player);
}

void	load_walls(t_textures *textures, t_game *game)
{
	mlx_texture_t	*wall;

	wall = mlx_load_png("./img/stone.png");
	if (wall == NULL)
		error_and_destroy("Loading wall failed", game);
	textures->wall = mlx_texture_to_image(game->mlx, wall);
	if (textures->wall == NULL)
	{
		mlx_delete_texture(wall);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->wall, PX, PX);
	mlx_delete_texture(wall);
}

void	load_floor(t_textures *textures, t_game *game)
{
	mlx_texture_t	*floor;

	floor = mlx_load_png("./img/hui.png");
	if (floor == NULL)
		error_and_destroy("Loading floor failed", game);
	textures->floor = mlx_texture_to_image(game->mlx, floor);
	if (textures->floor == NULL)
	{
		mlx_delete_texture(floor);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->floor, PX, PX);
	mlx_delete_texture(floor);
}

/*
void	load_player(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player;

	player = mlx_load_png("./img/demon.png");
	if (player == NULL)
		error_and_destroy("Loading player failed", game);
    textures->player_t = player;
	textures->player = mlx_texture_to_image(game->mlx, player);
	if (textures->player == NULL)
	{
		mlx_delete_texture(player);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->player, PX, PX);
    //mlx_delete_texture(player); removed since we will reuse it 
}
*/