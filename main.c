/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/02 13:40:09 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	check_command_line(ac, av);
	game = get_basic_data(av[1]);
	printf("height %d\n", game->map_height); // remove
	printf("width %d\n", game->map_width);  // remove
	printf("PPOS_X %d\n", game->ppos_x);     // remove
	printf("PPOS_Y %d\n", game->ppos_y);     // remove
	printf("EPOS_X %d\n", game->epos_x);     // remove
	printf("EPOS_Y %d\n", game->epos_y);     // remove
	free(game);                       // added for now.
	return (0);                       // remove
}

t_game	*get_basic_data(char *input)
{
	char	*map_in_line;
	char	**map_splitted;
	t_game	*basic_data;

	int check = 0; // remove
	map_in_line = process_map(input);
	validate_map(map_in_line);
	map_splitted = ft_split(map_in_line, '\n');
	if (map_splitted == NULL)
		error_on_validation("Split failed", map_in_line);
	free(map_in_line);
	basic_data = init_basic_data(map_splitted);
    validate_path(basic_data);
	while (map_splitted[check]) // remove all
	{
		printf("%s\n", map_splitted[check]);
		check++;
	}
	free_map(map_splitted); // remove
	return (basic_data);    // remove
}


void    validate_path(t_game *basic_data)
{
    char **map_dup;
    int i;
    int j;
    
    i = 0;
    map_dup = duplicate(basic_data);
    if(map_dup == NULL)
        error_and_destroy("Malloc faild during path validation", basic_data);
    flood_fill(map_dup, basic_data->ppos_x, basic_data->ppos_y);


}

void    flood_fill(char **map_dup, int x, int y)
{
     if(map_dup[x][y] == '1' || map_dup[x][y] == 'W')
        return ;
    if(map_dup[x][y] == 'E')
    {
        map_dup[x][y] = '1';
        return ;
    }
    if(map_dup[x][y] == '0' || map_dup[x][y] == 'C' || map_dup[x][y] == 'P')
        map_dup[x][y] = 'W';
    flood_fill(map_dup, x - 1, y); // up
    flood_fill(map_dup, x + 1, y); // ))
    flood_fill(map_dup, x, y - 1); // left
    flood_fill(map_dup, x , y + 1);// right
}

char    **duplicate(t_game *basic_data)
{
    int i;
    char **map_dup;
    
    i = 0;
    map_dup = malloc(sizeof(char *) * (basic_data->map_height + 1));
    if(map_dup == NULL)
        return (NULL);
    while(i < basic_data->map_height)
    {
        map_dup[i] = ft_strdup(basic_data->map[i]);
        if(map_dup[i] == NULL)
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
			error_message("Malloc failed");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	close(fd);
	return (joined);
}
