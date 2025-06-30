/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/30 14:51:13 by mklevero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_game
{
	char	**map;
	int		width;
	int		height;

}			t_game;

// main
int			main(int ac, char **av);

// terminal input check
void		check_input(int ac, char **av);

// init data
t_game		*init_base_data(char *input);

// map operations
char		*process_map(char *input);
void		validate_map(char *map_in_line);
void		check_valid_input(char *contents);
void		check_invalid_input(char *contents);
void		check_empty_lines(char *contents);

// helpers
char		*join_together(char *s1, char *s2);

// error handling
void		error_message(char *message);
void		error_on_validation(char *message, char *str);

#endif