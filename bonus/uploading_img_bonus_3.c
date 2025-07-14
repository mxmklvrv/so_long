/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uploading_img_bonus_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:24:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/09 19:03:59 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
		annihilate("Loading texture to img player ate left side failed.", game,
			1);
	}
	mlx_resize_image(textures->player_ate_left, PX, PX);
}

void	load_player_dying_0(t_textures *textures, t_game *game)
{
	mlx_texture_t *player_dead_0;

	player_dead_0 = mlx_load_png("./img/smert0.png");
	if (player_dead_0 == NULL)
		annihilate("Loading player ate failed.", game, 1);
	textures->player_td_0 = player_dead_0;
	textures->player_dead_0 = mlx_texture_to_image(game->mlx, player_dead_0);
	if (textures->player_dead_0 == NULL)
	{
		mlx_delete_texture(player_dead_0);
		annihilate("Loading texture to img player ate left side failed.", game,
			1);
	}
	mlx_resize_image(textures->player_dead_0, PX, PX);
}

void	load_player_dying(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player_dead;

	player_dead = mlx_load_png("./img/smert.png");
	if (player_dead == NULL)
		annihilate("Loading player ate failed.", game, 1);
	textures->player_td = player_dead;
	textures->player_dead = mlx_texture_to_image(game->mlx, player_dead);
	if (textures->player_dead == NULL)
	{
		mlx_delete_texture(player_dead);
		annihilate("Loading texture to img player ate left side failed.", game,
			1);
	}
	mlx_resize_image(textures->player_dead, PX, PX);
}

void	load_player_dying_2(t_textures *textures, t_game *game)
{
	mlx_texture_t *player_dead_2;

	player_dead_2 = mlx_load_png("./img/smert_2.png");
	if (player_dead_2 == NULL)
		annihilate("Loading player ate failed.", game, 1);
	textures->player_td_2 = player_dead_2;
	textures->player_dead_2 = mlx_texture_to_image(game->mlx, player_dead_2);
	if (textures->player_dead_2 == NULL)
	{
		mlx_delete_texture(player_dead_2);
		annihilate("Loading texture to img player ate left side failed.", game,
			1);
	}
	mlx_resize_image(textures->player_dead_2, PX, PX);
}

