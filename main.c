/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/26 20:53:10 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	check_input(ac, av);
	game = init_base_data(av[1]);
}

t_game	*init_base_data(char *input)
{
	char	*map_in_line;
	char	**map_splitted;
	t_game	*data;

	map_in_line = process_map(input);
	if (map_in_line == NULL)
		error_message("so... cannot read file");
}

char	*process_map(char *input) // leaking af 
{
	int		fd;
	char	*solo;
	char	*joined;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_message("so... cannot open file");
	joined = ft_strdup("");
	if (joined == NULL)
		return (NULL);
	while (1)
	{
		solo = get_next_line(fd);
		if (solo)
		{
			joined = join(joined, solo);
			if (joined == NULL)
			{
				free(joined);
				error_message("so... malloc failed");
			}
			free(solo);
		}
		else
			break ;
	}
	close(fd);
	return (joined);
	
}

char	*join(char *s1, char *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	len_total;
	char	*joined;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	len_total = len_1 + len_2;
	joined = (char *)malloc(sizeof(char) * (len_total + 1));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, len_total + 1);
	ft_strlcat(joined, s2, len_total + 1);
	free(s1);
	return (joined);
}

void	check_input(int ac, char **av)
{
	int	av_len;

	if (ac != 2)
	{
		if (ac < 2)
			error_message("so... not enough arguments");
		else
			error_message("so... too much arguments");
	}
	av_len = ft_strlen(av[1]);
	if (av_len <= 4 || ft_strncmp(av[1] + av_len - 4, ".ber", 4) != 0)
		error_message("so... provide a valid .ber file");
}

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	exit(1);
}


char	*get_map_str(char *file_name)
{
	int		fd;
	char	*next_line;
	char	*map_str;

	map_str = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_exit("Cannot open the map 🗺️");
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break;
		map_str = so_strjoin(map_str, next_line);
		if (!map_str)
		{
			free(map_str);
			error_exit("malloc function broke");
		}
		free (next_line);
	}

	return (map_str);
}
