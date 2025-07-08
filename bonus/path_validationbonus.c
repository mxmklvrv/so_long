/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validationbonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:19:44 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 01:53:44 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	validate_path(t_game *basic_data)
{
	char	**map_dup;
	int		i;
	int		j;

	i = 0;
	map_dup = duplicate(basic_data);
	if (map_dup == NULL)
		annihilate("Malloc failed during path validation.", basic_data, 1);
	flood_fill(map_dup, basic_data->ppos_x, basic_data->ppos_y);
	while (i < basic_data->map_height)
	{
		j = 0;
		while (j < basic_data->map_width)
		{
			if (map_dup[i][j] != '1' && map_dup[i][j] != '0'
				&& map_dup[i][j] != '~' && map_dup[i][j] != 'D')
			{
				free_map(map_dup);
				annihilate("Cannot find a valid path.", basic_data, 1);
			}
			j++;
		}
		i++;
	}
	free_map(map_dup);
}

void	flood_fill(char **map_dup, int x, int y)
{
	if (map_dup[y][x] == '1' || map_dup[y][x] == 'D' || map_dup[y][x] == '~')
		return ;
	if (map_dup[y][x] == 'E')
	{
		map_dup[y][x] = '1';
		return ;
	}
	if (map_dup[y][x] == '0' || map_dup[y][x] == 'C' || map_dup[y][x] == 'P')
		map_dup[y][x] = '~';
	flood_fill(map_dup, x - 1, y);
	flood_fill(map_dup, x + 1, y);
	flood_fill(map_dup, x, y - 1);
	flood_fill(map_dup, x, y + 1);
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
