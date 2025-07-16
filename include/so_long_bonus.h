/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/16 15:10:15 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdbool.h>
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
	mlx_image_t		*flower;
	mlx_image_t		*exit_closed;
	mlx_image_t		*steps_on_screen;
	mlx_image_t		*player_ate;
	mlx_image_t		*player_ate_left;
	mlx_image_t		*player_dead_0;
	mlx_image_t		*player_dead;
	mlx_image_t		*player_dead_2;

	mlx_texture_t	*player_t;
	mlx_texture_t	*player_t_l;
	mlx_texture_t	*player_ta;
	mlx_texture_t	*player_ta_l;
	mlx_texture_t	*player_td_0;
	mlx_texture_t	*player_td;
	mlx_texture_t	*player_td_2;

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

	bool			dying;
	int				death_frame;
	int				loop_count;

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
void				game_status(t_game *game);

// bonus
void				load_bonus(t_textures *textures, t_game *game);
void				load_player_left(t_textures *textures, t_game *game);
void				load_flower(t_textures *textures, t_game *game);
void				load_exit_closed(t_textures *textures, t_game *game);
void				bonus_status(t_game *game);
void				steps_to_screen(t_game *game);
void				load_player_ate(t_textures *textures, t_game *game);
void				load_player_ate_left(t_textures *textures, t_game *game);
void				free_bonus_textures(t_game *game);
void				check_face_side(t_game *game);
void				redraw_player(t_game *game);
void				handle_step(t_game *game);
void				load_player_dying_0(t_textures *textures, t_game *game);
void				load_player_dying(t_textures *textures, t_game *game);
void				load_player_dying_2(t_textures *textures, t_game *game);

// death animation
void				death(void *tmp);
void				delete_img(t_game *game);
void				load_death_frame(t_game *game);

// error free exit
void				error_message(char *message);
void				error_on_validation(char *message, char *str);
void				annihilate(char *message, t_game *game, int decider);
void				free_map(char **map_splitted);
void				gnl_and_close(int fd);
void				free_textures(t_game *game);
void				early_termination(t_game *game);

#endif