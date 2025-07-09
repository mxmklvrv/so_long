/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_img_bonus_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:21:30 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/09 17:24:34 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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

	exit_closed = mlx_load_png("./img/zakrito.png");
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
