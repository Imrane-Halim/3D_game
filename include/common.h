/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:19 by imrane            #+#    #+#             */
/*   Updated: 2025/04/08 11:39:44 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_image
{
	char		*path;
	
	void		*img;
	void		*adr;
	int			bbp;
	int			line_length;
	int			endian;

	int			width;
	int			height;
}				t_image;

typedef struct s_textures
{
	t_image		north;
	t_image		south;
	t_image		east;
	t_image		west;
	t_image		door;
}				t_textures;

typedef struct s_scene
{
	int			m_width;
	int			m_height;
	char		**map;

	// things like floor, ceiling color, player direction
	// wall images... etc will be added later
	int			ceiling_color;
	int			floor_color;

	t_textures	textures;

}				t_scene;

t_scene			parse_map(char *path);

#endif