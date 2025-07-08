/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/08 20:25:40 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
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

	mlx_image_t		*player_left;
	mlx_image_t		*demon;
	mlx_image_t		*exit_closed;
	mlx_image_t		*steps_on_screen;

	mlx_texture_t	*player_t;
	mlx_texture_t	*player_t_l;

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
	char			dir;

}					t_game;

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
void				redraw_player(t_game *game, int decider);
void				game_status(t_game *game);

// bonus
void				redraw_player_left(t_game *game, int decider);
void				load_bonus(t_textures *textures, t_game *game);
void				load_player_left(t_textures *textures, t_game *game);
void				load_demon(t_textures *textures, t_game *game);
void				load_exit_closed(t_textures *textures, t_game *game);
void				bonus_status(t_game *game);
void				steps_to_screen(t_game *game);
void				check_face_dir_coll(t_game *game);
void				check_face_dir_zero(t_game *game);

// error free exit
void				error_message(char *message);
void				error_on_validation(char *message, char *str);
void				annihilate(char *message, t_game *game, int decider);
void				free_map(char **map_splitted);
void				gnl_and_close(int fd);
void				free_textures(t_game *game);
void				early_termination(t_game *game);

#endif