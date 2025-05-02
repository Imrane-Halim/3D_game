/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:00:50 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/02 11:52:05 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**take_copy(char **string)
{
	int		i;
	char	**copy;

	i = 0;
	while (string[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (string[i])
	{
		copy[i] = ft_strdup(string[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

bool	flood_fill(char **map, int i, int j)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (i < 0 || j < 0 || !map[i] || map[i][j] == '\0')
		return (false);
	if (map[i][j] == '1' || map[i][j] == 'v')
		return (true);
	if (map[i][j] == ' ')
		return (false);
	map[i][j] = 'v';
	up = flood_fill(map, i - 1, j);
	down = flood_fill(map, i + 1, j);
	left = flood_fill(map, i, j - 1);
	right = flood_fill(map, i, j + 1);
	return (up && down && left && right);
}

bool	check_wall(char **map)
{
	char	**copy;
	int		i;
	int		j;
	bool	check;

	i = 1;
	j = 1;
	copy = take_copy(map);
	set_player_position(copy, &i, &j);
	check = flood_fill(copy, i, j);
	free_2d_array(copy);
	return (check);
}
