/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:41:04 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 01:17:23 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_message(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(message, 2);
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

void	error_and_destroy(char *message, t_game *game)
{
	if (game->map)
		free_map(game->map);
	if (game->textures)
		free_textures(game);
    if (game->mlx)
        mlx_terminate(game->mlx);
	free(game);
	error_message(message);
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

void	free_textures(t_game *game)
{
	if (game->textures->floor)
		mlx_delete_image(game->mlx, game->textures->floor);
	if (game->textures->wall)
		mlx_delete_image(game->mlx, game->textures->wall);
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	if (game->textures->exit)
		mlx_delete_image(game->mlx, game->textures->exit);
	if (game->textures->collect)
		mlx_delete_image(game->mlx, game->textures->collect);
	free(game->textures);
}
