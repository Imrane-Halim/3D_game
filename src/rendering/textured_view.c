#include "cub3d.h"

static void	draw_floor_ceiling()
{
	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, g_game.scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2, WIDTH, g_game.scene.floor_color);
}

// this will be added later
// static int		shade_color(int color, float dist)
// {
// 	float	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
// 	int r = ((color >> 16) & 0xff) * factor;
// 	int g = ((color >> 8) & 0xff) * factor;
// 	int b = ((color) & 0xff) * factor;
// 	return (r << 16 | g << 8 | b);
// }

static int	get_pixel_color(t_image tex, t_xy pos)
{
	char	*src;
	int		x;
	int		y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (x < 0 || y < 0 || x >= tex.width || y >= tex.height)
		return (0);
	src = tex.adr + (y * tex.line_length + x * (tex.bbp / 8));
	return (*(unsigned int *)src);
}

static void	draw_tex_slice(t_ray ray, t_image tex, int bottom, int top, int x)
{
	(void)ray;
	int color = 0xff;
	for (int y = top; y < bottom; y++)
	{
		color = get_pixel_color(tex, (t_xy){24, 45});
		put_pixel((t_xy){x, y}, color);
	}
}

static void	draw_slice(t_ray ray, float ray_angle, int ray_num)
{
	float	dist = distance(g_game.player.pos, ray.hit) * cos(ray_angle - g_game.player.angle);
	float	wall_height = (TILESIZE / dist) * ((WIDTH / 2) / tan(FOV * PI / 360));
	int		wall_top = (HEIGHT - wall_height) / 2;
	int		wall_bottom = wall_top + wall_height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;

	t_image tex = g_game.scene.textures.west;
	if (ray.dir == NORTH)
		tex = g_game.scene.textures.north;
	else if (ray.dir == SOUTH)
		tex = g_game.scene.textures.south;
	else if (ray.dir == EAST)
		tex = g_game.scene.textures.east;
		
	draw_tex_slice(ray, tex, wall_bottom, wall_top, ray_num);
}

inline void	draw_textured()
{
	draw_floor_ceiling();

	t_ray	ray;
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
