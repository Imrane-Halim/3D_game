/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:22:58 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/06 08:40:52 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_2d_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_variables(char **colors, char **map, char **paths)
{
	free_2d_array(paths);
	free_2d_array(map);
	free_2d_array(colors);
}

void	free_image(t_image *img)
{
	if (img->path)
		free(img->path);
}

void	free_textures(t_textures *textures)
{
	free_image(&textures->north);
	free_image(&textures->south);
	free_image(&textures->east);
	free_image(&textures->west);
	free_image(&textures->door);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_2d_array(scene->map);
	free_textures(&scene->textures);
	free(scene);
}
