/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:05:43 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/02 17:48:11 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



void	check_command_line(int ac, char **av)
{
	int	av_len;

	if (ac != 2)
	{
		if (ac < 2)
			error_message("Not enough arguments");
		else
			error_message("Too much arguments");
	}
	av_len = ft_strlen(av[1]);
	if (av_len <= 4 || ft_strncmp(av[1] + av_len - 4, ".ber", 4) != 0)
		error_message("Provide a valid .ber file");
}

int	get_height(char **map_splitted)
{
	int	i;

	i = 0;
	while (map_splitted[i])
		i++;
	return (i);
}

int	get_pos(t_game *data, char object, char axes)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == object)
			{
				if (axes == 'x')
					return (x);
				else if (axes == 'y')
					return (y);
			}
			x++;
		}
		y++;
	}
	return (0);
}
