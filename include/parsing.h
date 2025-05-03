/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:13 by imrane            #+#    #+#             */
/*   Updated: 2025/05/03 12:48:28 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "common.h"
# include "cub3d.h"

t_scene	*parse_map(char *path);

void	free_scene(t_scene *scene);
bool	check(char *str, char *prefix);
bool	check_prefix(char **paths);
bool	extract_paths(char **paths);
bool	fill_paths(char *content, int *i, char **paths);
bool	edit_colors(char ***head);
char	*my_malloc(char c, char *string);
void	free_2d_array(char **array);
void	free_variables(char **colors, char **mapchar, char **paths);
bool	extract_paths_2(char **paths);
void	set_paths_textures(t_scene **scene, char **paths);
char	**get_paths_textures(char *content, int *i);
bool	convert_colors_to_int(char **colors, int *rgb);
void	set_colors(t_scene *scene, char **colors);
char	**get_colors(char *content, int *i);

char	**get_map(char *content, int *i);
bool	check_char(char **map);
t_scene	*init_scene(char *content);
char	*file_to_string(char *path);
bool	check_size(char **map);

char	**take_copy(char **string);
bool	check_wall(char **map);
void	set_player_position(char **string, int *i, int *j);
void	print_2d_array(char **array);
void	set_height_width(t_scene *scene);
bool	is_player_char(char c);

int		check_extension(char *path);

#endif