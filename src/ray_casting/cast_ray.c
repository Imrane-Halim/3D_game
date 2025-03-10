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

/*
// to prototypes, nothing serious overhere....

	t_xy cast_ray(float angle) {
    float px = g_game.player.pos.x;
    float py = g_game.player.pos.y;
    float dir_x = cos(angle);
    float dir_y = sin(angle);

    // Vertical intersections
    t_xy vert_hit = find_vertical_hit(px, py, dir_x, dir_y);
    // Horizontal intersections
    t_xy horiz_hit = find_horizontal_hit(px, py, dir_x, dir_y);

    // Compare distances and return closest hit
    if (distance(vert_hit) < distance(horiz_hit))
        return vert_hit;
    else
        return horiz_hit;
}
*/


/*
source: https://permadi.com/1996/05/ray-casting-tutorial-7/
--------->finding horizontal intersection: 

1. find the coordinates of the first ever point, let's call it A
	--> for y:
	if (ray facing up)
		A.y = ((int)player.y / TILESIZE) * TILESIZE - 1;
	if (ray facing down)
		A.y = ((int)player.y / TILESIZE) * TILESIZE + TILESIZE;
	
	some explanation:
		we must decide whether A is part of the block above the grid line, 
		that is why we substract -1 from A.y
	
	--> for x:
	A.x = player.x + (player.y - A.y) / tan (RAY_ANGLE)

2. find offsets
	if (ray facing up)
		Ya = -TILESIZE;
	if (ray facing down)
		Ya = TILESIZE;
	
	Xa = TILESIZE / tan(FOV)

3. check the grid for a wall
4. if there is no wall, move to next point:
	Ynew = Yold + Ya;
	Xnew = Xold + Xa;
*/


t_xy find_vertical_hit(t_xy p, float angle)
{
    t_xy A;
    t_xy Offset;
    
    if (angle > PI/2 && angle < 3*PI/2)
	{
        A.x = ((int)p.x / TILESIZE) * TILESIZE - 1;
        Offset.x = -TILESIZE;
    }
	else
	{
        A.x = ((int)p.x / TILESIZE) * TILESIZE + TILESIZE;
        Offset.x = TILESIZE;
    }
    A.y = p.y + (p.x - A.x) * tan(angle);
    Offset.y = Offset.x * tan(angle);
    while (true)
	{
        if (A.x < 0 || A.x >= WIDTH || A.y < 0 || A.y >= HEIGHT)
            break;
            
        if (obj_hit(A) == '1')
            break;
            
        A.x += Offset.x;
        A.y += Offset.y;
    }
    return A;
}

t_xy find_horizontal_hit(t_xy p, float angle)
{
    t_xy A;
    t_xy Offset;
    
    if (angle > PI && angle < 2*PI)
	{
        A.y = ((int)p.y / TILESIZE) * TILESIZE - 1;
        Offset.y = -TILESIZE;
    }
	else
	{
        A.y = ((int)p.y / TILESIZE) * TILESIZE + TILESIZE;
        Offset.y = TILESIZE;
    }
    A.x = p.x + (p.y - A.y) / tan(angle);
    Offset.x = TILESIZE / tan(angle);
    while (true)
	{
        if (A.x < 0 || A.x >= WIDTH || A.y < 0 || A.y >= HEIGHT)
            break;
            
        if (obj_hit(A) == '1')
            break;
            
        A.x += Offset.x;
        A.y += Offset.y;
    }
    return A;
}

float	distance(t_xy a, t_xy b)
{
	return (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)));
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