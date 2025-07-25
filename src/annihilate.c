/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annihilate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:32:41 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 16:07:08 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	annihilate(char *message, t_game *game, int decider)
{
	if (game)
	{
		if (game->map)
			free_map(game->map);
		if (game->textures)
			free_textures(game);
		if (game->mlx)
		{
			mlx_close_window(game->mlx);
			mlx_terminate(game->mlx);
		}
		free(game);
	}
	if (decider == 1)
		error_message(message);
	else if (decider == 2)
	{
		ft_putendl_fd(message, 1);
		exit(0);
	}
	ft_putstr_fd(message, 1);
	exit(0);
}

void	free_textures(t_game *game)
{
	if (!game || !game->textures)
		return ;
	if (game->textures->floor)
		mlx_delete_image(game->mlx, game->textures->floor);
	if (game->textures->wall)
		mlx_delete_image(game->mlx, game->textures->wall);
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	if (game->textures->exit)
		mlx_delete_image(game->mlx, game->textures->exit);
	if (game->textures->collect)
		mlx_delete_image(game->mlx, game->textures->collect);
	if (game->textures->player_t)
		mlx_delete_texture(game->textures->player_t);
	free(game->textures);
}
