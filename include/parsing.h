/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:13 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 16:03:27 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "common.h"
# include "cub3d.h"
# include <errno.h>

// errors
# define EXTENSION_ERR "Invalid file extension! Please use `.cub`."
# define IDENTIFIER_ERR "Missing, invalid, or duplicated identifier detected."
# define NEWLINE_ERR "Unexpected newline character found in the map."
# define INVALIDCHAR_ERR "Invalid characters found in the map."
# define PLAYER_ERR "The map must contain exactly one\
player. Found none or multiple."
# define WALL_ERR "The map walls are not properly closed."
# define NOMAP_ERR "No map found in file"

// lists to check
# define PLAYER_CHARS "NSEW"
# define ALLOWED_CHARS "01DNSWE \n"

// for the `find_char_in_line` function
# define IN_LIST 1
# define NOT_IN_LIST 0

typedef enum s_param
{
	eNO = (1 << 0),
	eSO = (1 << 1),
	eEA = (1 << 2),
	eWE = (1 << 3),
	eF = (1 << 4),
	eC = (1 << 5),
	ePLAYER_FOUND = (1 << 6)
}				t_param;

// extern short	parsed;

// common utils
bool			is_in_arr(char *value, const char *arr[]);
int				count_args(char **arr);
void			free_arr(char **arr);
char			**add_line_to_arr(char **arr, char *line);
char			*find_char_in_line(char *line, char *chars, int find_type);
void			ft_close(t_scene *scene, char *line, char *reason);

// identifier functions
int				process_identifier(t_scene *scene, char **args);

// map parsing funtions
void			load_map(t_scene *scene, char *line);
void			check_walls(t_scene *scene);

// parsing stages
void			parse_identifiers(t_scene *scene);
void			parse_map(t_scene *scene);

#endif