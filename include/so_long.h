/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/05 15:29:11 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h> // remove
# include <stdlib.h>
# include <unistd.h>

# define PX 64

typedef struct s_textures
{
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*player;
	mlx_image_t		*exit;
	mlx_image_t		*collect;

	mlx_texture_t	*player_t;

}					t_textures;

typedef struct s_game
{
	t_textures		*textures;
	mlx_t			*mlx;
	char			**map;

	int				map_width;
	int				map_height;
	int				ppos_x;
	int				ppos_y;
	int				epos_x;
	int				epos_y;
	int				loot;
	int				looted;
	int				steps;

}					t_game;

// UDALI ETO
void				print_args(char **argv);

// main
int					main(int ac, char **av);

// init data
t_game				*get_basic_data(char *input);
t_game				*init_basic_data(char **map_splitted);
t_textures			*init_textures(t_game *game);

// map validation
char				*process_map(char *input);
void				validate_map(char *map_in_line);
void				check_valid_input(char *contents);
void				check_invalid_input(char *contents);
void				check_empty_lines(char *contents);
void				check_minimum_rows(char *contents);
void				check_map_form(char *contents);
void				check_walls(char *contents);
void				confirm_wall(char *contents, int start, int len,
						int decider);

// path validation
void				validate_path(t_game *basic_data);
void				flood_fill(char **map_dup, int x, int y);
char				**duplicate(t_game *basic_data);

// create window and textures
void				start_game(t_game *game);
void				load_map(t_game *game);
void				load_rest(t_game *game, int x, int y);

void				load_floor(t_textures *textures, t_game *game);
void				load_exit(t_textures *textures, t_game *game);
void				load_loot(t_textures *textures, t_game *game);
void				load_player(t_textures *textures, t_game *game);
void				load_walls(t_textures *textures, t_game *game);

// helpers
char				*join_together(char *s1, char *s2);
void				check_command_line(int ac, char **av);
int					get_height(char **map_splitted);
int					get_pos(t_game *data, char object, char axis);
int					count_loot(t_game *data);

// gameplay
void				move_hook(mlx_key_data_t keydata, void *param);
void				action(t_game *game, char dir);
void				redraw_player(t_game *game);

// error and free handling
void				error_message(char *message);
void				error_on_validation(char *message, char *str);
void				error_and_destroy(char *message, t_game *game);
void				free_map(char **map_splitted);
void				gnl_and_close(int fd);
void				free_textures(t_game *game);

#endif