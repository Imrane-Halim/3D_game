/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:50:45 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 14:33:27 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// ----- these functions check palyer position, invalid chars... etc
int	check_player_pos(t_scene *scene, char *line)
{
	char	*line_pos;
	t_xy	pos;

	line_pos = find_char_in_line(line, PLAYER_CHARS, IN_LIST);
	if (!line_pos)
		return (0);
	if (scene->parsed & ePLAYER_FOUND)
		return (1);
	scene->parsed |= ePLAYER_FOUND;
	pos.y = (scene->m_height) * 64;
	pos.x = (line_pos - line) * 64;
	if (line_pos[0] == 'N')
		init_player(pos, PI + PI / 2);
	if (line_pos[0] == 'S')
		init_player(pos, PI / 2);
	if (line_pos[0] == 'E')
		init_player(pos, 0);
	if (line_pos[0] == 'W')
		init_player(pos, PI);
	return (0);
}

void	load_map(t_scene *scene, char *line)
{
	while (line)
	{
		if (line[0] == '\n')
			ft_close(scene, line, NEWLINE_ERR);
		if (find_char_in_line(line, ALLOWED_CHARS, NOT_IN_LIST))
			ft_close(scene, line, INVALIDCHAR_ERR);
		if (check_player_pos(scene, line))
			ft_close(scene, line, PLAYER_ERR);
		if (ft_strrchr(line, '\n'))
			*ft_strrchr(line, '\n') = '\0';
		scene->m_height++;
		scene->map = add_line_to_arr(scene->map, line);
		if (ft_strlen(line) > (size_t)scene->m_width)
			scene->m_width = ft_strlen(line);
		line = get_next_line(scene->fd);
	}
	if ((scene->parsed & ePLAYER_FOUND) == 0)
		ft_close(scene, NULL, PLAYER_ERR);
}
