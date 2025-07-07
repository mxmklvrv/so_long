/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:41:04 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/07 13:35:27 by mklevero         ###   ########.fr       */
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

void    early_termination(t_game *game)
{
    annihilate("Early exit", game, 0);
}

void	annihilate(char *message, t_game *game, int decider)
{
    if (game)
    {
        if (game->map)
            free_map(game->map);
        if (game->textures)
            free_textures(game);
        if (game->mlx)
        {
            mlx_close_window(game->mlx);
            mlx_terminate(game->mlx);
        }
        free(game);
    }
    if(desider == 1)
        error_message(message);
    else
    {
        ft_putendl_fd(message);
        exit(0);
    }
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
    if (!game || !game->textures)
        return;
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
    if (game->textures->player_t)
        mlx_delete_texture(game->textures->player_t);
    free(game->textures);
}
