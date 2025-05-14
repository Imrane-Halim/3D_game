/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:23:38 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 11:03:37 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline char	obj_hit(t_game *game, t_xy cord)
{
	int	map_x;
	int	map_y;

	map_x = (int)(cord.x / TILESIZE);
	map_y = (int)(cord.y / TILESIZE);
	if (map_y < 0 || map_y >= game->scene.m_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->scene.map[map_y]))
		return (0);
	return (game->scene.map[map_y][map_x]);
}

static inline t_ray	get_hit(t_game *game, t_ray A, t_xy step)
{
	while (true)
	{
		if (obj_hit(game, A.hit) == 'D')
			A.dir = DOOR;
		if (obj_hit(game, A.hit) != '0' && obj_hit(game, A.hit) != 'O')
			break ;
		A.hit.x += step.x;
		A.hit.y += step.y;
	}
	return (A);
}

static inline t_ray	find_vertical_hit(t_game *game, t_xy p, float angle)
{
	t_ray	first_hit;
	t_xy	step;

	if (cos(angle) > 0)
	{
		first_hit.hit.x = floor(p.x / TILESIZE) * TILESIZE + TILESIZE;
		first_hit.dir = EAST;
		step.x = TILESIZE;
	}
	else
	{
		first_hit.hit.x = floor(p.x / TILESIZE) * TILESIZE - 0.0001;
		first_hit.dir = WEST;
		step.x = -TILESIZE;
	}
	first_hit.hit.y = p.y + (first_hit.hit.x - p.x) * tan(angle);
	step.y = step.x * tan(angle);
	return (get_hit(game, first_hit, step));
}

static inline t_ray	find_horizontal_hit(t_game *game, t_xy p, float angle)
{
	t_ray	first_hit;
	t_xy	step;

	if (sin(angle) > 0)
	{
		first_hit.hit.y = floor(p.y / TILESIZE) * TILESIZE + TILESIZE;
		first_hit.dir = SOUTH;
		step.y = TILESIZE;
	}
	else
	{
		first_hit.hit.y = floor(p.y / TILESIZE) * TILESIZE - 0.0001;
		first_hit.dir = NORTH;
		step.y = -TILESIZE;
	}
	first_hit.hit.x = p.x + (first_hit.hit.y - p.y) / tan(angle);
	step.x = step.y / tan(angle);
	return (get_hit(game, first_hit, step));
}

// note: angle is in radian
inline t_ray	cast_ray(t_game *game, float angle)
{
	t_xy	player;
	t_ray	vert_hit;
	t_ray	horiz_hit;

	player = game->player.pos;
	vert_hit = find_vertical_hit(game, player, angle);
	horiz_hit = find_horizontal_hit(game, player, angle);
	if (distance(player, vert_hit.hit) < distance(player, horiz_hit.hit))
		return (vert_hit);
	return (horiz_hit);
}
