/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:05:43 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/01 16:00:27 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*join_together(char *s1, char *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*joined;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		len_1 = 0;
	else
		len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (joined == NULL)
	{
		free(s1);
		return (NULL);
	}
	if (s1 != NULL)
		ft_memcpy(joined, s1, len_1);
	ft_memcpy(joined + len_1, s2, len_2);
	joined[len_1 + len_2] = '\0';
	free(s1);
	return (joined);
}

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

void	get_height(char **map_splitted)
{
	int	i;

	i = 0;
	while (map_splitted[i])
		i++;
	return (i);
}
