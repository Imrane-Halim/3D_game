/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:50:19 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 16:03:42 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// bits will be used as flags
// short	parsed = 0;

// --- common utils
void	ft_close(t_scene *scene, char *line, char *reason)
{
	scene->map = add_line_to_arr(scene->map, line);
	g_game()->scene = *scene;
	close_game(EXIT_FAILURE, reason);
}

// --- opening the file
int	open_file(char *path)
{
	int		fd;
	char	*ext;

	ext = ft_strrchr(path, '.');
	if (!ext)
		close_game(EXIT_FAILURE, EXTENSION_ERR);
	if (ft_strcmp(ext, ".cub"))
		close_game(EXIT_FAILURE, EXTENSION_ERR);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		close_game(EXIT_FAILURE, strerror(errno));
	return (fd);
}

// --- first stage of parsing (identifiers)
void	parse_identifiers(t_scene *scene)
{
	char	*line;
	char	**args;

	line = NULL;
	args = NULL;
	while (true)
	{
		free(line);
		if (scene->parsed == (eNO + eSO + eWE + eEA + eC + eF))
			break ;
		line = get_next_line(scene->fd);
		if (!line)
			break ;
		if (line[0] == '\n')
			continue ;
		args = ft_split(line, ' ');
		if (process_identifier(scene, args))
		{
			free(line);
			free_arr(args);
			g_game()->scene = *scene;
			close_game(EXIT_FAILURE, IDENTIFIER_ERR);
		}
		free_arr(args);
	}
}

// --- second stage of parsing (map)
void	parse_map(t_scene *scene)
{
	int		flag;
	char	*line;

	flag = 0;
	line = NULL;
	while (true)
	{
		free(line);
		line = get_next_line(scene->fd);
		if (!line)
			break ;
		if (line[0] == '\n' && !flag)
			continue ;
		flag = 1;
		break ;
	}
	if (!line)
	{
		g_game()->scene = *scene;
		close_game(EXIT_FAILURE, NOMAP_ERR);
	}
	load_map(scene, line);
	g_game()->scene = *scene;
	check_walls(scene);
}

t_scene	parse_scene(char *path)
{
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	scene.fd = open_file(path);
	parse_identifiers(&scene);
	parse_map(&scene);
	return (scene);
}
