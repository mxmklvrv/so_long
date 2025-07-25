/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/16 14:10:46 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	data->loot = count_loot(data);
	data->looted = 0;
	data->steps = 0;
	data->textures = NULL;
	data->mlx = NULL;
	return (data);
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(game->map_width * PX, game->map_height * PX, "so_long",
			true);
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
	textures->exit = NULL;
	textures->collect = NULL;
	textures->player_t = NULL;
	load_floor(textures, game);
	load_walls(textures, game);
	load_player(textures, game);
	load_loot(textures, game);
	load_exit(textures, game);
	return (textures);
}
