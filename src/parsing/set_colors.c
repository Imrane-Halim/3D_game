/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:53:15 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/02 11:57:29 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_colors(t_scene *scene, char **colors)
{
	int	rgb[2];

	convert_colors_to_int(colors, rgb);
	scene->floor_color = rgb[0];
	scene->ceiling_color = rgb[1];
	free_2d_array(colors);
}

bool	check_prefix_colors(char **colors)
{
	if (!check(colors[0], "F"))
		return (false);
	if (!check(colors[1], "C"))
		return (false);
	return (true);
}

bool	edit_colors(char ***head)
{
	char	*tmp;
	char	**colors;
	char	*new_color;
	int		i;

	colors = *head;
	i = -1;
	if (!check_prefix_colors(colors))
		return (false);
	while (++i < 2)
	{
		tmp = ft_strchr(colors[i], ' ');
		if (!tmp)
			return (false);
		while (*tmp && *tmp == ' ')
			tmp++;
		if (!*tmp)
			return (false);
		new_color = ft_strdup(tmp);
		free(colors[i]);
		colors[i] = new_color;
		if (!colors[i])
			return (false);
	}
	return (true);
}

bool	check_colors(char **colors)
{
	int		i;
	char	*tmp;

	if (!check_prefix_colors(colors))
		return (false);
	i = 0;
	while (i < 2)
	{
		tmp = ft_strchr(colors[0], ' ');
		if (!tmp || !*tmp)
			return (false);
		free(colors[i]);
		colors[i] = ft_strdup(tmp);
		if (!colors[i])
		{
			free_2d_array(colors);
			return (false);
		}
		i++;
	}
	return (true);
}
