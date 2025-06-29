/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/27 18:04:02 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	*game;

	check_input(ac, av);
	game = init_base_data(av[1]);
	return (0);
}

t_game	*init_base_data(char *input)
{
	char	*map_in_line;
	char	**map_splitted;
	t_game	*data;

	map_in_line = process_map(input);
	validate_map(map_in_line);
	printf("%s", map_in_line);
	free(map_in_line);
	return (0);
}
void	error_on_validation(char *message, char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	free(str);
	exit(1);
}

void	validate_map(char *map_in_line)
{
	check_on_empty(map_in_line);
	// check on smth else
}
void	check_on_empty(char *contents)
{
	int	i;

	i = 0;
	if (contents == NULL)
		error_on_validation("so... just an empty file", contents);
	if (contents[0] == '\n')
		error_on_validation("so... an empty line detected", contents);
	while (contents[i])
	{
		if (contents[i] == '\n' && contents[i + 1] == '\n')
			error_on_validation("so... part of map is missing", contents);
		i++;
	}
}

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
	exit(1);
}

char	*process_map(char *input)
{
	int		fd;
	char	*solo;
	char	*joined;
	char	*tempo;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		error_message("so... cannot open file");
	joined = NULL;
	solo = get_next_line(fd);
	while (solo)
	{
		tempo = join_together(joined, solo);
		free(solo);
		if (tempo == NULL)
		{
			free(joined);
			error_message("so... malloc failed");
		}
		joined = tempo;
		solo = get_next_line(fd);
	}
	close(fd);
	return (joined);
}

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
