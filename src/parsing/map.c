/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:49:44 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/02 11:49:45 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_height_width(t_scene *scene)
{
	int	i;
	int	len;

	i = 0;
	scene->m_height = 0;
	scene->m_width = 0;
	while (scene->map[i])
	{
		len = ft_strlen(scene->map[i]);
		if (len > scene->m_width)
			scene->m_width = len;
		scene->m_height++;
		i++;
	}
}

bool	check_valid_map(char **map)
{
	if (!check_size(map))
		return (false);
	if (!check_char(map))
		return (false);
	if (!check_wall(map))
		return (false);
	return (true);
}

char	**get_map(char *content, int *i)
{
	char	**map;

	while (content[*i] && content[*i] == '\n')
		(*i)++;
	if (!content[*i])
		return (NULL);
	map = ft_split(content + *i, '\n');
	if (!map || !*map)
	{
		free_2d_array(map);
		return (NULL);
	}
	if (!check_valid_map(map))
	{
		free_2d_array(map);
		return (NULL);
	}
	return (map);
}
