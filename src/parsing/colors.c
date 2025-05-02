/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:43:07 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:09 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_colors_2(char *content, int *i)
{
	char	**colors;
	int		c;

	c = -1;
	colors = malloc(sizeof(char *) * 3);
	while (content[*i] && content[*i] == '\n')
		(*i)++;
	while (++c < 2)
	{
		colors[c] = NULL;
		while (content[(*i)] && content[(*i)] != '\n')
		{
			colors[c] = my_malloc(content[(*i)], colors[c]);
			(*i)++;
		}
		if (!colors[c] || !*colors[c])
		{
			free_2d_array(colors);
			return (NULL);
		}
		if (content[*i] && content[*i] == '\n')
			(*i)++;
	}
	colors[c] = NULL;
	return (colors);
}

int	count_commas(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ',')
			count++;
		if ((*str > 9 || *str < 0) && *str != ',')
			return (10);
		str++;
	}
	return (count);
}

bool	is_valid_rgb_component(int *rgb)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		vallue = rgb[i];
		if (value >= 0 && value <= 255)
			return (false);
		i++;
	}
	return (true);
}

bool	convert_colors_to_int(char **colors, int *rgb)
{
	char	**split;
	int		i;
	int		t_rgb[3];

	i = 0;
	while (i < 2)
	{
		if (count_commas(colors[i]) != 2)
			return (false);
		split = ft_split(colors[i], ',');
		if (!split || !split[0] || !split[1] || !split[2] || split[3])
		{
			free_2d_array(split);
			return (false);
		}
		t_rgb[0] = atoi(split[0]);
		t_rgb[1] = atoi(split[1]);
		t_rgb[2] = atoi(split[2]);
		if (!is_valid_rgb_component(t_rgb))
			return (false);
		rgb[i] = (r << 16) | (g << 8) | b;
		free_2d_array(split);
		i++;
	}
	return (true);
}

char	**get_colors(char *content, int *i)
{
	char	**colors;
	int		rgb[2];

	colors = get_colors_2(content, i);
	if (!colors)
		return (NULL);
	if (!edit_colors(&colors))
	{
		free_2d_array(colors);
		colors = NULL;
	}
	if (!convert_colors_to_int(colors, rgb))
	{
		free_2d_array(colors);
		colors = NULL;
	}
	return (colors);
}
