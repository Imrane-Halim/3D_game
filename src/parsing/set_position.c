/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:02:42 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/03 12:43:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	set_player_position(char **string, int *i, int *j)
{
	int	row;
	int	col;

	row = 0;
	while (string[row])
	{
		col = 0;
		while (string[row][col])
		{
			if (is_player_char(string[row][col]))
			{
				*i = row;
				*j = col;
				return ;
			}
			col++;
		}
		row++;
	}
	*i = -1;
	*j = -1;
}
