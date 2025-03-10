#include "cub3d.h"

char obj_hit(t_xy cord)
{
    int map_x = (int)(cord.x / TILESIZE);
    int map_y = (int)(cord.y / TILESIZE);
    
    if (map_x < 0 || map_x >= g_game.scene.m_width)
        return (0);
    if (map_y < 0 || map_y >= g_game.scene.m_height)
        return (0);
    return (g_game.scene.map[map_y][map_x]);
}

float	distance(t_xy a, t_xy b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
}

t_xy find_vertical_hit(t_xy p, float angle)
{
    (void)p; (void)angle;
    return (t_xy){0, 0};
}

t_xy find_horizontal_hit(t_xy p, float angle)
{
    (void)p; (void)angle;
    return (t_xy){0, 0};
}

// note: angle is in radian
t_xy	cast_ray(float angle)
{
    t_xy player = g_game.player.pos;

    t_xy vert_hit = find_vertical_hit(player, angle);
    t_xy horiz_hit = find_horizontal_hit(player, angle);

    if (distance(player, vert_hit) < distance(player, horiz_hit))
        return (vert_hit);
    return (horiz_hit);
}