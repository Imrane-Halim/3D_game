/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:51:44 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 10:59:42 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_tex_dir(short *parsed, t_image *img, t_param dir, char *path)
{
	char	*nl;

	if (*parsed & dir)
		return (1);
	nl = ft_strchr(path, '\n');
	if (nl)
		*nl = '\0';
	img->path = ft_strdup(path);
	*parsed |= dir;
	return (0);
}

int	get_tex_dir(t_scene *scene, char **args)
{
	if (!ft_strncmp("NO", args[0], 2))
		return (set_tex_dir(&scene->parsed,
				&scene->textures.north, eNO, args[1]));
	else if (!ft_strncmp("SO", args[0], 2))
		return (set_tex_dir(&scene->parsed,
				&scene->textures.south, eSO, args[1]));
	else if (!ft_strncmp("WE", args[0], 2))
		return (set_tex_dir(&scene->parsed,
				&scene->textures.west, eWE, args[1]));
	return (set_tex_dir(&scene->parsed,
			&scene->textures.east, eEA, args[1]));
}

// --- get color
int	set_color(short *parsed, int *scene, int clr_value, t_param wall)
{
	if (*parsed & wall)
		return (1);
	*scene = clr_value;
	*parsed |= wall;
	return (0);
}

int	get_clr(t_scene *scene, char **args)
{
	char	**colors;
	char	*nl;
	long	rgb[3];

	nl = ft_strchr(args[1], '\n');
	if (nl)
		*nl = '\0';
	colors = ft_split(args[1], ',');
	if (count_args(colors) != 3)
		return (free_arr(colors), 1);
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	free_arr(colors);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		return (1);
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (1);
	if (args[0][0] == 'F')
		return (set_color(&scene->parsed, &scene->floor_color,
				(rgb[0] << 16) | (rgb[1] << 8) | (rgb[2]), eF));
	return (set_color(&scene->parsed, &scene->ceiling_color,
			(rgb[0] << 16) | (rgb[1] << 8) | (rgb[2]), eC));
}

// --- processing identifiers (NO, SO, F...)
int	process_identifier(t_scene *scene, char **args)
{
	static const char	*dirs[] = {"NO", "SO", "WE", "EA", NULL};
	static const char	*clrs[] = {"C", "F", NULL};

	if (count_args(args) != 2
		&& scene->parsed != (eNO + eSO + eWE + eEA + eC + eF))
		return (1);
	if (is_in_arr(args[0], dirs))
	{
		if (get_tex_dir(scene, args))
			return (1);
	}
	else if (is_in_arr(args[0], clrs))
	{
		if (get_clr(scene, args))
			return (1);
	}
	else
		return (1);
	return (0);
}
