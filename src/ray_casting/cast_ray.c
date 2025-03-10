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

t_xy	cast_ray(float angle)
{
	(void)angle;
	return (t_xy){0, 0};
}