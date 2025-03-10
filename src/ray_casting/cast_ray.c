#include "cub3d.h"

float	calcMagnitude(t_xy cord)
{
	return (sqrt(cord.x * cord.x + cord.y * cord.y));
}

t_xy	normlVector(t_xy vector)
{
	float	m;
	t_xy	new_v;

	m = calcMagnitude(vector);
	new_v.x = vector.x / m;
	new_v.y = vector.y / m;
	return (new_v);
}

bool hit_obj(t_xy cord, char obj)
{
    int map_x = (int)(cord.x / TILESIZE);
    int map_y = (int)(cord.y / TILESIZE);
    
    if (map_x < 0 || map_x >= g_game.scene.m_width)
        return (false);
    if (map_y < 0 || map_y >= g_game.scene.m_height)
        return (false);
    
    return (g_game.scene.map[map_y][map_x] == obj);
}

t_xy	cast_ray(float angle)
{
	t_xy 	ray;
	t_xy 	incr;
	float	max;

	ray = g_game.player.pos;
	incr.x = cos(angle);
	incr.y = sin(angle);
	max = WIDTH;
	while (true)
	{
		ray.x += incr.x;
		ray.y += incr.y;
		if (ray.x < 0 || ray.x >= max)
			break ;
		if (ray.y < 0 || ray.y >= max)
			break ;
		if (hit_obj(ray, '1'))
			break ;
	}
	return (ray);
}