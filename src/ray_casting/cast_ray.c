#include "cub3d.h"

inline char obj_hit(t_xy cord)
{
	int map_x = (int)(cord.x / TILESIZE);
	int map_y = (int)(cord.y / TILESIZE);
	
	if (map_x < 0 || map_x >= g_game.scene.m_width)
		return (0);
	if (map_y < 0 || map_y >= g_game.scene.m_height)
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

inline t_xy find_vertical_hit(t_xy p, float angle)
{
	t_xy	A;
	t_xy	step;

	if (cos(angle) > 0)
	{
		A.x = floor(p.x / TILESIZE) * TILESIZE + TILESIZE;
		step.x = TILESIZE;
	}
	else
	{
		A.x = floor(p.x / TILESIZE) * TILESIZE - 0.0001;
		step.x = -TILESIZE;
	}
	A.y = p.y + (A.x - p.x) * tan(angle);
	step.y = step.x * tan(angle);
	return (get_hit(A, step));
}

inline t_xy find_horizontal_hit(t_xy p, float angle)
{
	t_xy	A;
	t_xy	step;

	if (sin(angle) > 0)
	{
		A.y = floor(p.y / TILESIZE) * TILESIZE + TILESIZE;
		step.y = TILESIZE;
	}
	else
	{
		A.y = floor(p.y / TILESIZE) * TILESIZE - 0.0001;
		step.y = -TILESIZE;
	}
	A.x = p.x + (A.y - p.y) / tan(angle);
	step.x = step.y / tan(angle);
	return (get_hit(A, step));
}

// note: angle is in radian
inline t_xy	cast_ray(float angle)
{
	t_xy player = g_game.player.pos;

	t_xy vert_hit = find_vertical_hit(player, angle);
	t_xy horiz_hit = find_horizontal_hit(player, angle);

	if (distance(player, vert_hit) < distance(player, horiz_hit))
		return (vert_hit);
	return (horiz_hit);
}