/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:56:13 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/16 13:56:39 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	death(void *tmp)
{
	t_game	*game;

	game = tmp;
	if (game->dying == false)
		return ;
	if (++game->loop_count < 30)
		return ;
	game->loop_count = 0;
	load_death_frame(game);
	game->death_frame++;
	if (game->death_frame >= 3)
	{
		game->dying = false;
		annihilate("You ate poisoned flower, gg ez))\n", game, 0);
	}
}

void	load_death_frame(t_game *game)
{
	int				control;
	mlx_image_t		*image;
	mlx_texture_t	*frame[3];

	control = 0;
	frame[0] = game->textures->player_td_0;
	frame[1] = game->textures->player_td;
	frame[2] = game->textures->player_td_2;
	delete_img(game);
	image = mlx_texture_to_image(game->mlx, frame[game->death_frame]);
	if (image == NULL)
		annihilate("Failed to load death.", game, 1);
	mlx_resize_image(image, PX, PX);
	control = mlx_image_to_window(game->mlx, image, game->ppos_x * PX,
			game->ppos_y * PX);
	if (control < 0)
		annihilate("Failed to load death.", game, 1);
	if (game->dir == 'l')
		game->textures->player_left = image;
	else
		game->textures->player = image;
}
