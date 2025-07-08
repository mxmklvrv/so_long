/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:59:52 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 19:45:53 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
	if (count_nl > 32)
		error_on_validation("Map is too tall.", contents);
}

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
	if (first_row > 61)
		error_on_validation("Map is too wide.", contents);
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
				error_on_validation("First and last rows must be filled with 1.",
					contents);
			i++;
		}
	}
	else
	{
		if (contents[start] != '1' || contents[start + len - 1] != '1')
			error_on_validation("Mid row must start&end with 1.", contents);
	}
}
