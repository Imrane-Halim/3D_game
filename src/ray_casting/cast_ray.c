#include "cub3d.h"

/*

	int floor(px / 64);
	check cos >< 0
	< 0 
	px += 64
	> 0
	px -= 1;
	r = px / cos;
	py_x = sin * r;

(px,py_x)

	int floor(py/64);
	check sin >< 0
	< 0
	py += 64;
	>0
	py --;
	r = py / sin;
	px_y = r * cos

(px_y,py)

*/

// this function returns the xy where the ray stops
// (aka hit an obsticle)
t_xy	cast_ray(float angle)
{
	(void)angle;

	return (t_xy){0, 0};
}