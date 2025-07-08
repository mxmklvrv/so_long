/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_img_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:52:15 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/09 01:22:09 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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

	player = mlx_load_png("./img/player.png");
	if (player == NULL)
		annihilate("Loading player failed.", game, 1);
	textures->player_t = player;
	textures->player = mlx_texture_to_image(game->mlx, player);
	if (textures->player == NULL)
		annihilate("Loading texture to img failed.", game, 1);
	mlx_resize_image(textures->player, PX, PX);
}


// bonus part

void	load_player_left(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player_left;

	player_left = mlx_load_png("./img/player_left.png");
	if (player_left == NULL)
		annihilate("Loading player left side failed.", game, 1);
	textures->player_t_l = player_left;
	textures->player_left = mlx_texture_to_image(game->mlx, player_left);
	if (textures->player_left == NULL)
    {
        mlx_delete_texture(player_left);
        annihilate("Loading texture to img player left side failed.", game, 1);
    }
	mlx_resize_image(textures->player_left, PX, PX);
}

void	load_flower(t_textures *textures, t_game *game)
{
	mlx_texture_t	*flower;

	flower = mlx_load_png("./img/flower.png");
	if (flower == NULL)
		annihilate("Loading demon failed.", game, 1);
	textures->flower = mlx_texture_to_image(game->mlx, flower);
	if (textures->flower == NULL)
	{
		mlx_delete_texture(flower);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->flower, PX, PX);
	mlx_delete_texture(flower);
}

void	load_exit_closed(t_textures *textures, t_game *game)
{
	mlx_texture_t	*exit_closed;

	exit_closed = mlx_load_png("./img/exit_closed.png");
	if (exit_closed == NULL)
		annihilate("Loading closed exit failed.", game, 1);
	textures->exit_closed = mlx_texture_to_image(game->mlx, exit_closed);
	if (textures->exit_closed == NULL)
	{
		mlx_delete_texture(exit_closed);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->exit_closed, PX, PX);
	mlx_delete_texture(exit_closed);
}

void	steps_to_screen(t_game *game)
{
	char	*count;
	char	*str;

	count = ft_itoa(game->steps);
	if (count == NULL)
		annihilate("Steps to screen failed.", game, 1);
	str = ft_strjoin("MOVES: ", count);
	free(count);
	if (str == NULL)
		annihilate("Steps to screen failed.", game, 1);
	if (game->textures->steps_on_screen)
		mlx_delete_image(game->mlx, game->textures->steps_on_screen);
	game->textures->steps_on_screen = mlx_put_string(game->mlx, str,
			(game->map_width * PX) / 2, game->map_height * PX);
	if (game->textures->steps_on_screen == NULL)
	{
		free(str);
		annihilate("Steps to screen failed.", game, 1);
	}
	free(str);
}

void	load_player_ate(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player_ate;

	player_ate = mlx_load_png("./img/player_ate.png");
	if (player_ate == NULL)
		annihilate("Loading player ate failed.", game, 1);
	textures->player_ta = player_ate;
	textures->player_ate = mlx_texture_to_image(game->mlx, player_ate);
	if (textures->player_ate == NULL)
    {
        mlx_delete_texture(player_ate);
        annihilate("Loading texture to img player ate side failed.", game, 1);
    }
	mlx_resize_image(textures->player_ate, PX, PX);
}

void	load_player_ate_left(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player_ate_left;

	player_ate_left = mlx_load_png("./img/player_ate_left.png");
	if (player_ate_left == NULL)
		annihilate("Loading player ate failed.", game, 1);
	textures->player_ta_l = player_ate_left;
	textures->player_ate_left = mlx_texture_to_image(game->mlx,
			player_ate_left);
	if (textures->player_ate_left == NULL)
     {
        mlx_delete_texture(player_ate_left);
        annihilate("Loading texture to img player ate left side failed.", game, 1);
     }
	mlx_resize_image(textures->player_ate_left, PX, PX);
}

