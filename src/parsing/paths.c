/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:42:54 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/05 10:26:37 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	extract_paths(char **paths)
{
	if (!paths)
		return (false);
	if (!check_prefix(paths))
	{
		free_2d_array(paths);
		return (false);
	}
	if (!extract_paths_2(paths))
	{
		printf("Cannot extract the Path.\n");
		free_2d_array(paths);
		return (false);
	}
	return (true);
}

void	set_paths_textures(t_scene **scene, char **paths)
{
	(*scene)->textures.north.path = ft_strdup(paths[0]);
	(*scene)->textures.south.path = ft_strdup(paths[1]);
	(*scene)->textures.west.path = ft_strdup(paths[2]);
	(*scene)->textures.east.path = ft_strdup(paths[3]);
	(*scene)->textures.door.path = "textures/xpm/door.xpm";
	g_game()->hand.path = "textures/xpm/hand.xpm";
	free_2d_array(paths);
}

bool	fill_paths(char *content, int *i, char **paths)
{
	int	p;

	p = 0;
	while (p < 4 && content[*i])
	{
		paths[p] = NULL;
		while (content[*i] && content[*i] != '\n')
		{
			paths[p] = my_malloc(content[*i], paths[p]);
			(*i)++;
		}
		if (!paths[p])
			return (false);
		if (content[*i] && content[*i] == '\n')
			(*i)++;
		p++;
	}
	paths[p] = NULL;
	return (true);
}

char	**get_paths_textures(char *content, int *i)
{
	char	**paths;
	int		p;

	paths = malloc(sizeof(char *) * 5);
	if (!paths)
		return (NULL);
	p = 0;
	while (content[*i] && content[*i] == '\n')
		(*i)++;
	if (!fill_paths(content, i, paths))
	{
		free_2d_array(paths);
		paths = NULL;
	}
	if (!extract_paths(paths))
		paths = NULL;
	return (paths);
}
