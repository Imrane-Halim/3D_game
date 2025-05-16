/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:49:55 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 18:32:29 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// ----- walls validation functions
int	check_boarders(char *line)
{
	while (*line && (*line == ' ' || *line == '1'))
		line++;
	if (*line)
		return (1);
	return (0);
}

int	check_edges(char *line)
{
	char	*last;

	while (*line && *line == ' ')
		line++;
	if (*line != '1')
		return (1);
	last = ft_strrchr(line, '\0');
	if (last)
		last--;
	while (line < last && *last == ' ')
		last--;
	if (*last != '1')
		return (1);
	return (0);
}

int	check_prev_line(char **map, int i, int num)
{
	char	*prev_line;

	if ((size_t)i > ft_strlen(map[num - 1]))
		return (0);
	prev_line = map[num - 1] + i;
	while (*prev_line)
	{
		if (*prev_line == '0' || ft_strchr(PLAYER_CHARS "D", *prev_line))
			return (1);
		prev_line++;
	}
	return (0);
}

// this function is a bit unreadalbe because of fkn norminette
int	check_interior(char **map, char *line, int num)
{
	char	*allowed_chars;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || ft_strchr(PLAYER_CHARS"0D", line[i]))
		{
			if (line[i] == ' ')
				allowed_chars = " 1";
			else
				allowed_chars = "01" PLAYER_CHARS "D";
			if ((size_t)i > ft_strlen(map[num - 1]) && line[i] != ' ')
				return (1);
			if (!ft_strchr(allowed_chars, map[num - 1][i]))
				return (1);
			if (!ft_strchr(allowed_chars, line[i + 1]))
				return (1);
		}
		i++;
	}
	return (check_prev_line(map, i, num));
}

void	check_walls(t_scene *scene)
{
	int	i;

	if (check_boarders(scene->map[0])
		|| check_boarders(scene->map[scene->m_height - 1]))
		close_game(EXIT_FAILURE, WALL_ERR);
	i = 1;
	while (i < scene->m_height - 1)
	{
		if (check_edges(scene->map[i]))
			close_game(EXIT_FAILURE, WALL_ERR);
		if (check_interior(scene->map, scene->map[i], i))
			close_game(EXIT_FAILURE, WALL_ERR);
		i++;
	}
}
