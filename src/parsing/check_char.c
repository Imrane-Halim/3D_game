/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:26 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/06 15:57:01 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	check_zero(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && (j == 0 || !map[i][j + 1]))
				return (false);
			if (map[i][j] == '0' && j > 0 && map[i][j - 1] == ' ')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	other_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_player_char(map[i][j]) && map[i][j] != '0' &&
				map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != 'D')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_char(char **map)
{
	int	i;
	int	j;
	int	check;
	int check_door;

	i = 0;
	check = 0;
	check_door = 0;
	if (!other_char(map) || !check_zero(map))
		return (false);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
				check++;
			if (map[i][j] == 'D')
				check_door++;
			j++;
		}
		i++;
	}
	return (check == 1 && check_door <= 1);
}
