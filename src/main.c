/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 15:28:54 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("argv[%d]: |%s|\n", i, argv[i]);
		i++;
	}
	printf("\n\n");
}

int	main(int ac, char **av)
{
	t_game	*game;

	check_command_line(ac, av);
	game = get_basic_data(av[1]);
	start_game(game);
	free(game); // added for now.
	return (0); // remove
}
void	start_game(t_game *game)
{
	game->mlx = mlx_init(game->map_width * PX, game->map_height * PX, "so_long",
			true);
	if (!game->mlx)
		error_and_destroy("Window creation failed", game);
	game->textures = init_textures(game);
	load_map(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_key_hook(game->mlx, move_hook, game);
	mlx_loop(game->mlx);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx); // or change it
	}
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
		redraw_player(game);
	}
	if ((dir == 'l') && (game->map[game->ppos_y][game->ppos_x - 1] != '1'))
	{
		game->ppos_x -= 1;
		redraw_player(game);
	}
	if ((dir == 'u') && (game->map[game->ppos_y - 1][game->ppos_x] != '1'))
	{
		game->ppos_y -= 1;
		redraw_player(game);
	}
	if ((dir == 'd') && (game->map[game->ppos_y + 1][game->ppos_x + 1] != '1'))
	{
		game->ppos_y += 1;
		redraw_player(game);
	}
}

void	redraw_player(t_game *game)
{
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	game->textures->player = mlx_texture_to_image(game->mlx,
			game->textures->player_t);
	if (game->textures->player == NULL)
		error_and_destroy("Failed to redraw player", game);
	mlx_resize_image(game->textures->player, PX, PX);
	mlx_image_to_window(game->mlx, game->textures->player, game->ppos_x * PX,
		game->ppos_y * PX);
}

void	load_map(t_game *game)
{
	int	x;
	int	y;
	int	control;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			control = 0;
			control = mlx_image_to_window(game->mlx, game->textures->floor, x
					* PX, y * PX);
			if (control < 0)
				error_and_destroy("Loading background failed", game);
			load_rest(game, x, y);
			x++;
		}
		y++;
	}
}

void	load_rest(t_game *game, int x, int y)
{
	int	control;

	control = 0;
	if (game->map[y][x] == 'P')
		control = mlx_image_to_window(game->mlx, game->textures->player, x * PX,
				y * PX);
	else if (game->map[y][x] == '1')
		control = mlx_image_to_window(game->mlx, game->textures->wall, x * PX, y
				* PX);
	else if (game->map[y][x] == 'E')
		control = mlx_image_to_window(game->mlx, game->textures->exit, x * PX, y
				* PX);
	else if (game->map[y][x] == 'C')
		control = mlx_image_to_window(game->mlx, game->textures->collect, x
				* PX, y * PX); // make smaller
	if (control < 0)
		error_and_destroy("Loading failed", game);
}

t_textures	*init_textures(t_game *game)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (textures == NULL)
		error_and_destroy("Malloc failed in textures init", game);
	textures->floor = NULL;
	textures->wall = NULL;
	textures->player = NULL;
	textures->exit = NULL;
	textures->collect = NULL;
	load_floor(textures, game);
	load_walls(textures, game);
	load_player(textures, game);
	load_loot(textures, game);
	load_exit(textures, game);
	return (textures);
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
		error_on_validation("Split failed", map_in_line);
	free(map_in_line);
	basic_data = init_basic_data(map_splitted);
	validate_path(basic_data);
	// free_map(map_splitted);
	return (basic_data); // remove
}

t_game	*init_basic_data(char **map_splitted)
{
	t_game	*data;

	data = malloc(sizeof(t_game));
	if (data == NULL)
	{
		free_map(map_splitted);
		error_message("Malloc failed in data init");
	}
	data->map = map_splitted;
	data->map_width = ft_strlen(map_splitted[0]);
	data->map_height = get_height(map_splitted);
	data->ppos_x = get_pos(data, 'P', 'x');
	data->ppos_y = get_pos(data, 'P', 'y');
	data->epos_x = get_pos(data, 'E', 'x');
	data->epos_y = get_pos(data, 'E', 'y');
	data->loot = count_loot(data);
	return (data);
}

char	*process_map(char *input)
{
	int		fd;
	char	*solo;
	char	*joined;
	char	*tempo;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_message("Cannot open file");
	joined = NULL;
	solo = get_next_line(fd);
	while (solo)
	{
		tempo = join_together(joined, solo);
		free(solo);
		if (tempo == NULL)
		{
			free(joined);
			gnl_and_close(fd);
			error_message("Malloc failed");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	gnl_and_close(fd);
	return (joined);
}
