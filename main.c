/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/30 19:39:25 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	check_command_line(ac, av);
	game = get_base_data(av[1]);
	return (0); // remove
}

t_game	*get_base_data(char *input)
{
	char	*map_in_line;
	char	**map_splitted;
	t_game	*base_data;

	int check = 0; // remove
	map_in_line = process_map(input);
	validate_map(map_in_line);
	map_splitted = ft_split(map_in_line, '\n');
	if (map_splitted == NULL)
		error_on_validation("Split failed", map_in_line);
	while (map_splitted[check]) // remove all
	{
		printf("%s\n", map_splitted[check]);
		check++;
	}
	free(map_in_line);      // remove
	free_map(map_splitted); // remove
	return (0);             // remove
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
			error_message("Malloc failed");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	close(fd);
	return (joined);
}
