/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:23:01 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 16:04:47 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		action(game, 'r');
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		action(game, 'l');
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
		redraw_player(game, 0);
	}
	else if ((dir == 'l') && (game->map[game->ppos_y][game->ppos_x - 1] != '1'))
	{
		game->ppos_x -= 1;
		redraw_player_left(game, 0);
	}
	else if ((dir == 'u') && (game->map[game->ppos_y - 1][game->ppos_x] != '1'))
	{
		game->ppos_y -= 1;
		redraw_player(game, 0);
	}
	else if ((dir == 'd') && (game->map[game->ppos_y + 1][game->ppos_x] != '1'))
	{
		game->ppos_y += 1;
		redraw_player(game, 0);
	}
	game_status(game);
	bonus_status(game);
}

void	bous_status(t_game *game)
{
	int	control;

	control = 0;
	if (game->map[game->ppos_y][game->ppos_x] == 'D')
	{
		// анимация смерти мб?
		ft_printf("You ate poisoned flower, gg ez))");
		annihilate("\n", game, 0);
	}
	if (game->loot == game->looted)
	{
		control = mlx_image_to_window(game->mlx, game->textures->exit,
				game->epos_x * PX, game->epos_x * PX);
		if (control < 0)
			annihilate("Failed to redraw exit.", game, 1);
	}
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
		redraw_player(game, 1);
		ft_printf("\033[1;33mFood eaten\n\033[0m");
		game->looted++;
		game->map[game->ppos_y][game->ppos_x] = '0';
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
}
