/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:35:34 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/27 13:16:23 by mklevero         ###   ########.fr       */
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
	while(solo)
	{
		tempo = join_together(joined, solo);
		free(solo);
		if(tempo == NULL)
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
		memcpy(joined, s1, len_1);
	memcpy(joined + len_1, s2, len_2);
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
