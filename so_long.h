/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/07/01 15:42:22 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h> // remove
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	char	**map;
	int		map_width;
	int		map_height;
	int		ppos_x;
	int		ppos_y;
	int		epos_x;
	int		epos_y;
	int		loot;
	int		looted;
	int		steps;

}			t_game;

// main
int			main(int ac, char **av);

// terminal input check
void		check_command_line(int ac, char **av);

// init data
t_game		*get_basic_data(char *input);

// map validation
char		*process_map(char *input);
void		validate_map(char *map_in_line);
void		check_valid_input(char *contents);
void		check_invalid_input(char *contents);
void		check_empty_lines(char *contents);
void		check_minimum_rows(char *contents);
void		check_map_form(char *contents);
void		check_walls(char *contents);
void		confirm_wall(char *contents, int start, int len, int decider);

// helpers
char		*join_together(char *s1, char *s2);
void		check_command_line(int ac, char **av);

// error and free handling
void		error_message(char *message);
void		error_on_validation(char *message, char *str);
void		error_and_destroy(char *message, t_game *game);
void		free_map(char **map_splitted);

#endif