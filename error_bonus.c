/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:41:04 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 01:53:21 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	error_message(char *message)
{
	ft_putstr_fd("\033[31mError\n", 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd("\033[0m", 2);
	exit(1);
}
void	gnl_and_close(int fd)
{
	close(fd);
	gnl_clear();
}

void	error_on_validation(char *message, char *str)
{
	free(str);
	error_message(message);
}

void	early_termination(t_game *game)
{
	annihilate("Early exit.", game, 2);
}

void	free_map(char **map_splitted)
{
	int	i;

	i = 0;
	if (map_splitted == NULL)
		return ;
	while (map_splitted[i])
		free(map_splitted[i++]);
	free(map_splitted);
	map_splitted = NULL;
}
