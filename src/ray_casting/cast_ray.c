#include "cub3d.h"

inline char obj_hit(t_xy cord)
{
	int map_x = (int)(cord.x / TILESIZE);
	int map_y = (int)(cord.y / TILESIZE);
	
	if (map_y < 0 || map_y >= g_game.scene.m_height)
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(g_game.scene.map[map_y]))
		return (0);
	return (g_game.scene.map[map_y][map_x]);
}

inline float	distance(t_xy a, t_xy b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

inline t_xy    get_hit(t_xy A, t_xy step)
{
    while (true)
	{
		if (obj_hit(A) != '0')
			break;
		A.x += step.x;
		A.y += step.y;
	}
    return (A);
}

inline t_ray find_vertical_hit(t_xy p, float angle)
{
	t_ray	A;
	t_xy	step;

	if (cos(angle) > 0)
	{
		A.hit.x = floor(p.x / TILESIZE) * TILESIZE + TILESIZE;
		A.dir = EAST;
		step.x = TILESIZE;
	}
	else
	{
		A.hit.x = floor(p.x / TILESIZE) * TILESIZE - 0.0001;
		A.dir = WEST;
		step.x = -TILESIZE;
	}
	A.hit.y = p.y + (A.hit.x - p.x) * tan(angle);
	step.y = step.x * tan(angle);
	A.hit = get_hit(A.hit, step);
	return (A);
}

inline t_ray find_horizontal_hit(t_xy p, float angle)
{
	t_ray	A;
	t_xy	step;

	if (sin(angle) > 0)
	{
		A.hit.y = floor(p.y / TILESIZE) * TILESIZE + TILESIZE;
		A.dir = SOUTH;
		step.y = TILESIZE;
	}
	else
	{
		A.hit.y = floor(p.y / TILESIZE) * TILESIZE - 0.0001;
		A.dir = NORTH;
		step.y = -TILESIZE;
	}
	A.hit.x = p.x + (A.hit.y - p.y) / tan(angle);
	step.x = step.y / tan(angle);
	A.hit = get_hit(A.hit, step);
	return (A);
}

// note: angle is in radian
inline t_ray	cast_ray(float angle)
{
	t_xy player = g_game.player.pos;

	t_ray vert_hit = find_vertical_hit(player, angle);
	t_ray horiz_hit = find_horizontal_hit(player, angle);

	if (distance(player, vert_hit.hit) < distance(player, horiz_hit.hit))
		return (vert_hit);
	return (horiz_hit);
}