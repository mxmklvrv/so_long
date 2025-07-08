/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:32:58 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 16:05:19 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

char	*process_map(char *input)
{
	int		fd;
	char	*solo;
	char	*joined;
	char	*tempo;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_message("Cannot open file.");
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
			error_message("Malloc failed.");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	gnl_and_close(fd);
	return (joined);
}

void	validate_map(char *map_in_line)
{
	check_empty_lines(map_in_line);
	check_invalid_input(map_in_line);
	check_valid_input(map_in_line);
	check_minimum_rows(map_in_line);
	check_map_form(map_in_line);
	check_walls(map_in_line);
}

void	check_empty_lines(char *contents)
{
	int	i;

	i = 0;
	if (contents == NULL)
		error_on_validation("Just an empty file.", contents);
	if (contents[0] == '\n')
		error_on_validation("An empty line detected.", contents);
	while (contents[i])
	{
		if (contents[i] == '\n' && contents[i + 1] == '\n')
			error_on_validation("Part of map is missing.", contents);
		i++;
	}
	if (contents[i - 1] == '\n')
		error_on_validation("An empty line at the end.", contents);
}

void	check_invalid_input(char *contents)
{
	int	i;

	i = 0;
	while (contents[i])
	{
		if (!ft_strchr("01PCED\n", contents[i]))
			error_on_validation("Invalid char in the map.", contents);
		i++;
	}
}

void	check_valid_input(char *contents)
{
	int	player;
	int	exit;
	int	collectible;
	int	demon;
	int	i;

	player = 0;
	exit = 0;
	collectible = 0;
	demon = 0;
	i = 0;
	while (contents[i])
	{
		if (contents[i] == 'P')
			player++;
		else if (contents[i] == 'E')
			exit++;
		else if (contents[i] == 'C')
			collectible++;
		else if (contents[i] == 'D')
			demon++;
		i++;
	}
	if (player != 1 || exit != 1 || demon < 0 || collectible == 0)
		error_on_validation("PECD validation failed.", contents);
}
