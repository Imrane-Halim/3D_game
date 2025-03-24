#include "cub3d.h"

static inline int	shade_color(int color, float dist)
{
	float	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
	int r = ((color >> 16) & 0xff) * factor;
	int g = ((color >> 8) & 0xff) * factor;
	int b = ((color) & 0xff) * factor;
	return (r << 16 | g << 8 | b);
}

inline int	get_pixel_color(t_image tex, t_xy pos)
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

static inline void draw_tex_slice(t_casted_ray cray, int bottom, int top)
{
	t_xy	tex_offset;
	float	start_y;
	float	wall_x;
	float	fractional_x;
	bool	is_vertical;

	is_vertical = (cray.ray.dir == EAST || cray.ray.dir == WEST);
	if (cray.ray.dir == DOOR)
	{
		fractional_x = cray.ray.hit.x - floor(cray.ray.hit.x / TILESIZE) * TILESIZE;
		is_vertical = (fractional_x < 0.001 || fractional_x > TILESIZE - 0.001);
	}
	if (is_vertical)
		wall_x = cray.ray.hit.y - floor(cray.ray.hit.y / TILESIZE) * TILESIZE;
	else
		wall_x = cray.ray.hit.x - floor(cray.ray.hit.x / TILESIZE) * TILESIZE;
	tex_offset.x = (int)((wall_x / TILESIZE) * cray.tex.width);
	start_y = (HEIGHT - cray.slice_hieght) / 2;
	while (top < bottom)
	{
		tex_offset.y = (int)(((top - start_y) / cray.slice_hieght) * cray.tex.height);
		put_pixel((t_xy){cray.ray_num, top}, shade_color(
			get_pixel_color(cray.tex, tex_offset), cray.dist));
		top++;
	}
}

static inline void	draw_slice(t_ray ray, float ray_angle, int ray_num)
{
	t_casted_ray cray;
	int		wall_top;
	int		wall_bottom;

	cray.dist = distance(g_game.player.pos, ray.hit)
		* cos(ray_angle - g_game.player.angle);
	cray.slice_hieght = (TILESIZE / cray.dist)
		* ((WIDTH / 2) / tan(FOV * PI / 360));
	cray.ray_num = ray_num;
	cray.ray = ray;
	wall_top = (HEIGHT - cray.slice_hieght) / 2;
	wall_bottom = wall_top + cray.slice_hieght;
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;
	cray.tex = g_game.scene.textures.door;
	if (ray.dir == NORTH)
		cray.tex = g_game.scene.textures.north;
	else if (ray.dir == SOUTH)
		cray.tex = g_game.scene.textures.south;
	else if (ray.dir == EAST)
		cray.tex = g_game.scene.textures.east;
	else if (ray.dir == WEST)
		cray.tex = g_game.scene.textures.west;
	draw_tex_slice(cray, wall_bottom, wall_top);
}

inline void	draw_textured()
{
	t_ray	ray;
	float	ray_angle;
	float	s_angle;
	float	angle_step;
	int		i;

	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH,
		g_game.scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2,
		WIDTH, g_game.scene.floor_color);
	
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
