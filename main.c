/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/02 18:11:57 by mklevero         ###   ########.fr       */
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
	if (!game)
		error_and_destroy("123", game);
	free(game); // added for now.
	return (0); // remove
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
	free_map(map_splitted);
	return (basic_data); // remove
}

void	validate_path(t_game *basic_data)
{
	char	**map_dup;
	int		i;
	int		j;

	i = 0;
	map_dup = duplicate(basic_data);
	if (map_dup == NULL)
		error_and_destroy("Malloc failed during path validation", basic_data);
	flood_fill(map_dup, basic_data->ppos_x, basic_data->ppos_y);
	while (i < basic_data->map_height)
	{
		j = 0;
		while (j < basic_data->map_width)
		{
			if (map_dup[i][j] != '1' && map_dup[i][j] != '0'
				&& map_dup[i][j] != '~')
			{
				free_map(map_dup);
				error_and_destroy("Cannot find a valid path", basic_data);
			}
			j++;
		}
		i++;
	}
	free_map(map_dup);
}

void	flood_fill(char **map_dup, int x, int y)
{
	if (map_dup[y][x] == '1' || map_dup[y][x] == '~')
		return ;
	if (map_dup[y][x] == 'E')
	{
		map_dup[y][x] = '1';
		return ;
	}
	if (map_dup[y][x] == '0' || map_dup[y][x] == 'C' || map_dup[y][x] == 'P')
		map_dup[y][x] = '~';
	print_args(map_dup);
	flood_fill(map_dup, x - 1, y); // up
	flood_fill(map_dup, x + 1, y); // ))
	flood_fill(map_dup, x, y - 1); // left
	flood_fill(map_dup, x, y + 1); // right
}

char	**duplicate(t_game *basic_data)
{
	int		i;
	char	**map_dup;

	i = 0;
	map_dup = malloc(sizeof(char *) * (basic_data->map_height + 1));
	if (map_dup == NULL)
		return (NULL);
	while (i < basic_data->map_height)
	{
		map_dup[i] = ft_strdup(basic_data->map[i]);
		if (map_dup[i] == NULL)
		{
			free_map(map_dup);
			return (NULL);
		}
		i++;
	}
	map_dup[i] = NULL;
	return (map_dup);
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
			close(fd);
			gnl_clear();
			error_message("Malloc failed");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	close(fd);
	gnl_clear();
	return (joined);
}
char	*join_together(char *s1, char *s2)
{
	size_t len_1;
	size_t len_2;
	char *joined;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		len_1 = 0;
	else
		len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (joined == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(joined, s1, len_1);
	ft_memcpy(joined + len_1, s2, len_2);
	joined[len_1 + len_2] = '\0';
	free(s1);
	return (joined);
}