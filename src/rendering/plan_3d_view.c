#include "cub3d.h"

void	draw_floor_ceiling()
{
	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, g_game.scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2, WIDTH, g_game.scene.floor_color);
}

int		shade_color(int color, float dist)
{
	float	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
	int r = ((color >> 16) & 0xff) * factor;
	int g = ((color >> 8) & 0xff) * factor;
	int b = ((color) & 0xff) * factor;
	return (r << 16 | g << 8 | b);
}

void	draw_slice(t_xy ray, float ray_angle, int ray_num)
{
	float	dist = distance(g_game.player.pos, ray) * cos(ray_angle - g_game.player.angle);
	float	wall_height = (TILESIZE / dist) * ((WIDTH / 2) / tan(FOV * PI / 360));
	int		wall_top = (HEIGHT - wall_height) / 2;
	int		wall_bottom = wall_top + wall_height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;
	int	shaded_color = shade_color(0xffffff, dist);
	draw_line((t_xy){ray_num, wall_top}, (t_xy){ray_num, wall_bottom}, shaded_color);
}

inline void	draw_3D_view(void)
{
	draw_floor_ceiling();

	t_xy	ray;
	float	ray_angle;

	float	s_angle;
	float	angle_step;

	int		i;

	i = 0;
	s_angle = g_game.player.angle - (FOV * PI / 180) / 2;
	angle_step = (FOV * PI / 180) / g_game.n_rays;
	while (i < g_game.n_rays)
	{
		ray_angle = s_angle + i * angle_step;
		ray = cast_ray(ray_angle);
		draw_slice(ray, ray_angle, i);
		i++;
	}
}
