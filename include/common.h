#ifndef COMMON_H
# define COMMON_H

# include <errno.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_scene
{
	int	m_width;
	int	m_height;
	char **map;

	// things like floor, ceiling color, player direction
	// wall images... etc will be added later
} t_scene;

t_scene	parse_map(char *path);

#endif