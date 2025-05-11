/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:26:03 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/11 09:26:59 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	angle_help(char m)
{
	if (m == 'N')
		return (PI / 2);
	if (m == 'W')
		return (PI);
	if (m == 'E')
		return (0);
	if (m == 'S')
		return (PI + PI / 2);
	return (-1);
}

float	get_correct_angle(void)
{
	int		i;
	int		j;
	char	**map;
	float	angle;

	map = g_game()->scene.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				angle = angle_help(map[i][j]);
				return (angle);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void	get_correct_pos(t_xy *pos)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = g_game()->scene.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
			{
				pos->x = j * 64;
				pos->y = i * 64;
				return ;
			}
			j++;
		}
		i++;
	}
}
