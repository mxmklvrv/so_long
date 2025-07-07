/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:52 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/07 17:00:00 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_form(char *contents)
{
	int	i;
	int	first_row;
	int	next_row;

	i = 0;
	first_row = 0;
	while (contents[i] != '\n')
	{
		first_row++;
		i++;
	}
	while (contents[i])
	{
		i++;
		next_row = 0;
		while (contents[i] != '\n' && contents[i] != '\0')
		{
			next_row++;
			i++;
		}
		if (first_row != next_row)
			error_on_validation("Not a rectangular shape.", contents);
	}
}

void	check_walls(char *contents)
{
	int	i;
	int	line;
	int	len;
	int	start;

	i = 0;
	line = 0;
	while (contents[i])
	{
		start = i;
		len = 0;
		while (contents[i] != '\n' && contents[i] != '\0')
		{
			len++;
			i++;
		}
		if (line == 0 || contents[i] == '\0')
			confirm_wall(contents, start, len, 1);
		else
			confirm_wall(contents, start, len, 0);
		if (contents[i] == '\n')
			i++;
		line++;
	}
}

void	confirm_wall(char *contents, int start, int len, int decider)
{
	int	i;

	i = 0;
	if (decider == 1)
	{
		while (i < len)
		{
			if (contents[start + i] != '1')
				error_on_validation("First and last must be all 1.", contents);
			i++;
		}
	}
	else
	{
		if (contents[start] != '1' || contents[start + len - 1] != '1')
			error_on_validation("Mid row must start&end with 1.", contents);
	}
}
