/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mklevero <mklevero@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:52:45 by mklevero          #+#    #+#             */
/*   Updated: 2025/06/27 13:12:46 by mklevero         ###   ########.fr       */
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

int			main(int ac, char **av);

void		check_input(int ac, char **av);

void		error_message(char *message);

t_game	*init_base_data(char *input);
char	*process_map(char *input);
char	*join_together(char *s1, char *s2);



#endif