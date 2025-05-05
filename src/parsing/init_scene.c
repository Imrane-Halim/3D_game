/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:50:11 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/05 09:35:03 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_scene	*init_scene(char *content)
{
	t_scene	*scene;
	char	**paths;
	char	**colors;
	char	**map;
	int		i;

	i = 0;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (NULL);
	paths = get_paths_textures(content, &i);
	colors = get_colors(content, &i);
	map = get_map(content, &i);
	if (!paths || !map || !colors)
	{
		free_variables(colors, map, paths);
		free(scene);
		return (NULL);
	}
	scene->map = map;
	set_paths_textures(&scene, paths);
	set_height_width(scene);
	set_colors(scene, colors);
	return (scene);
}
