#ifdef DEBUG

#include "cub3d.h"

static void	draw_floor_ceiling()
{
	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, g_game()->scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2,
		WIDTH, g_game()->scene.floor_color);
}

static int		shade_color(int color, float dist)
{
	float	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
	int r = ((color >> 16) & 0xff) * factor;
	int g = ((color >> 8) & 0xff) * factor;
	int b = ((color) & 0xff) * factor;
	return (r << 16 | g << 8 | b);
}

static void	draw_slice(t_ray ray, float ray_angle, int ray_num)
{
	float	dist = distance(g_game()->player.pos, ray.hit)
		* cos(ray_angle - g_game()->player.angle);
	float	wall_height = (TILESIZE / dist) 
		* ((WIDTH / 2) / tan(FOV * PI / 360));
	int		wall_top = (HEIGHT - wall_height) / 2;
	int		wall_bottom = wall_top + wall_height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;
	int color = 0;
	if (ray.dir == NORTH)
		color = 0xff0000;
	else if (ray.dir == SOUTH)
		color = 0x00ff00;
	else if (ray.dir == EAST)
		color = 0x0000ff;
	else if (ray.dir == WEST)
		color = 0xffff00;
	int	shaded_color = shade_color(color, dist);
	draw_line(g_game(), (t_xy){ray_num, wall_top}, 
		(t_xy){ray_num, wall_bottom}, shaded_color);
}

inline void	draw_3D_view(void)
{
	draw_floor_ceiling();

	t_ray	ray;
	float	ray_angle;

	float	s_angle;
	float	angle_step;

	int		i;

	i = 0;
	s_angle = g_game()->player.angle - (FOV * PI / 180) / 2;
	angle_step = (FOV * PI / 180) / g_game()->n_rays;
	while (i < g_game()->n_rays)
	{
		ray_angle = s_angle + i * angle_step;
		ray = cast_ray(g_game(), ray_angle);
		draw_slice(ray, ray_angle, i);
		i++;
	}
}

#endif