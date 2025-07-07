/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:32:58 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/07 17:00:27 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (!ft_strchr("01PCE\n", contents[i]))
			error_on_validation("Invalid char in the map.", contents);
		i++;
	}
}

void	check_valid_input(char *contents)
{
	int	player;
	int	exit;
	int	collectible;
	int	i;

	player = 0;
	exit = 0;
	collectible = 0;
	i = 0;
	while (contents[i])
	{
		if (contents[i] == 'P')
			player++;
		else if (contents[i] == 'E')
			exit++;
		else if (contents[i] == 'C')
			collectible++;
		i++;
	}
	if (player != 1 || exit != 1 || collectible == 0)
		error_on_validation("PEC validation failed.", contents);
}

void	check_minimum_rows(char *contents)
{
	int	i;
	int	count_nl;

	i = 0;
	count_nl = 0;
	while (contents[i])
	{
		if (contents[i] == '\n')
			count_nl++;
		i++;
	}
	if (count_nl < 2)
		error_on_validation("Not enough rows for map.", contents);
}
