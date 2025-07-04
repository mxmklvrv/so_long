/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/04 12:46:10 by mklevero         ###   ########.fr       */
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
	game->textures = init_textures(game->mlx, game);
	load_map(game);
	mlx_loop(game->mlx);
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
				* PX, y * PX);
	if (control < 0)
		error_and_destroy("Loading failed", game);
}

t_textures	*init_textures(mlx_t *mlx, t_game *game)
{
	t_textures	*textures;

	textures = malloc(sizeof(t_textures));
	if (textures == NULL)
		error_and_destroy("Malloc failed in textures init", game);
	load_floor(mlx, textures, game);
	load_walls(mlx, textures, game);
	load_player(mlx, textures, game);
	load_loot(mlx, textures, game);
	load_exit(mlx, textures, game);
	return (textures);
}

void	load_exit(mlx_t *mlx, t_textures *textures, t_game *game)
{
	mlx_texture_t	*exit;

	exit = mlx_load_png("./img/exit.png");
	if (exit == NULL)
		error_and_destroy("Loading exit failed", game);
	textures->exit = mlx_texture_to_image(mlx, exit);
	if (textures->exit == NULL)
	{
		mlx_delete_texture(exit);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->exit, PX, PX);
	mlx_delete_texture(exit);
}


void	load_loot(mlx_t *mlx, t_textures *textures, t_game *game)
{
	mlx_texture_t	*loot;

	loot = mlx_load_png("./img/collect.png");
	if (loot == NULL)
		error_and_destroy("Loading collectable failed", game);
	textures->collect = mlx_texture_to_image(mlx, loot);
	if (textures->collect == NULL)
	{
		mlx_delete_texture(loot);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->collect, PX, PX);
	mlx_delete_texture(loot);
}


void	load_player(mlx_t *mlx, t_textures *textures, t_game *game)
{
	mlx_texture_t	*player;

	player = mlx_load_png("./img/maga.png");
	if (player == NULL)
		error_and_destroy("Loading player failed", game);
	textures->player = mlx_texture_to_image(mlx, player);
	if (textures->player == NULL)
	{
		mlx_delete_texture(player);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->player, PX, PX);
	mlx_delete_texture(player);
}


void	load_walls(mlx_t *mlx, t_textures *textures, t_game *game)
{
	mlx_texture_t	*wall;

	wall = mlx_load_png("./img/wall_2.png");
	if (wall == NULL)
		error_and_destroy("Loading wall failed", game);
	textures->wall = mlx_texture_to_image(mlx, wall);
	if (textures->wall == NULL)
	{
		mlx_delete_texture(wall);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->wall, PX, PX);
	mlx_delete_texture(wall);
}


void	load_floor(mlx_t *mlx, t_textures *textures, t_game *game)
{
	mlx_texture_t	*floor;

	floor = mlx_load_png("./img/floor_2.png");
	if (floor == NULL)
		error_and_destroy("Loading floor failed", game);
	textures->floor = mlx_texture_to_image(mlx, floor);
	if (textures->floor == NULL)
	{
		mlx_delete_texture(floor);
		error_and_destroy("Loading texture to img failed", game);
	}
	mlx_resize_image(textures->floor, PX, PX);
	mlx_delete_texture(floor);
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
