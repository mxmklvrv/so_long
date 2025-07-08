/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 19:27:41 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	main(int ac, char **av)
{
	t_game	*game;

	check_command_line(ac, av);
	game = get_basic_data(av[1]);
	start_game(game);
	early_termination(game);
	return (0);
}
t_game	*get_basic_data(char *input)
{
	char	*map_in_line;
	char	**map_splitted;
	t_game	*basic_data;

	map_in_line = process_map(input);
	validate_map(map_in_line);
	map_splitted = ft_split(map_in_line, '\n');
	if (map_splitted == NULL)
		error_on_validation("Split failed.", map_in_line);
	free(map_in_line);
	basic_data = init_basic_data(map_splitted);
	validate_path(basic_data);
	return (basic_data);
}

t_game	*init_basic_data(char **map_splitted)
{
	t_game	*data;

	data = malloc(sizeof(t_game));
	if (data == NULL)
	{
		free_map(map_splitted);
		error_message("Malloc failed in data init.");
	}
	data->map = map_splitted;
	data->map_width = ft_strlen(map_splitted[0]);
	data->map_height = get_height(map_splitted);
	data->ppos_x = get_pos(data, 'P', 'x');
	data->ppos_y = get_pos(data, 'P', 'y');
	data->epos_x = get_pos(data, 'E', 'x');
	data->epos_y = get_pos(data, 'E', 'y');
	data->loot = count_loot(data);
	data->dir = 'r';
	data->looted = 0;
	data->steps = 0;
	data->textures = NULL;
	data->mlx = NULL;
	return (data);
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(game->map_width * PX, (game->map_height + 1) * PX,
			"so_long", true);
	if (!game->mlx)
		annihilate("Window creation failed.", game, 1);
	game->textures = init_textures(game);
	load_map(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(game->mlx, move_hook, game);
	mlx_loop(game->mlx);
}
t_textures	*init_textures(t_game *game)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (textures == NULL)
		annihilate("Malloc failed in textures init", game, 1);
	textures->floor = NULL;
	textures->wall = NULL;
	textures->player = NULL;
	textures->player_t = NULL;
	textures->exit = NULL;
	textures->collect = NULL;
	load_floor(textures, game);
	load_walls(textures, game);
	load_player(textures, game);
	load_loot(textures, game);
	load_exit(textures, game);
	load_bonus(textures, game);
	return (textures);
}

void	load_bonus(t_textures *textures, t_game *game)
{
	textures->player_left = NULL;
	textures->player_t_l = NULL;
	textures->demon = NULL;
	textures->exit_closed = NULL;
	textures->steps_on_screen = NULL;
	load_player_left(textures, game);
	load_demon(textures, game);
	load_exit_closed(textures, game);
}

void	load_player_left(t_textures *textures, t_game *game)
{
	mlx_texture_t	*player_left;

	player_left = mlx_load_png("./img/demon_left.png");
	if (player_left == NULL)
		annihilate("Loading player left side failed.", game, 1);
	textures->player_t_l = player_left;
	textures->player_left = mlx_texture_to_image(game->mlx, player_left);
	if (textures->player_left == NULL)
		annihilate("Loading texture to img player left side failed.", game, 1);
	mlx_resize_image(textures->player_left, PX, PX);
}

void	load_demon(t_textures *textures, t_game *game)
{
	mlx_texture_t	*demon;

	demon = mlx_load_png("./img/flower.png");
	if (demon == NULL)
		annihilate("Loading demon failed.", game, 1);
	textures->demon = mlx_texture_to_image(game->mlx, demon);
	if (textures->demon == NULL)
	{
		mlx_delete_texture(demon);
		annihilate("Loading texture to img failed.", game, 1);
	}
	mlx_resize_image(textures->demon, PX, PX);
	mlx_delete_texture(demon);
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
