/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_view.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:44 by imrane            #+#    #+#             */
/*   Updated: 2025/05/10 10:12:41 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static inline int	shade_color(int color, float dist)
{
	float	factor;
	int		r;
	int		g;
	int		b;

	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
	r = ((color >> 16) & 0xff) * factor;
	g = ((color >> 8) & 0xff) * factor;
	b = ((color) & 0xff) * factor;
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

static inline void	draw_tex_slice(t_game *game,
	t_casted_ray cray, int bottom, int top)
{
	t_xy	offset;
	float	st_y;
	float	wall_x;
	float	frac_x;
	bool	is_vertical;

	is_vertical = (cray.ray.dir == EAST || cray.ray.dir == WEST);
	if (cray.ray.dir == DOOR)
	{
		frac_x = cray.ray.hit.x - floor(cray.ray.hit.x / TILESIZE) * TILESIZE;
		is_vertical = (frac_x < 0.001 || frac_x > TILESIZE - 0.001);
	}
	if (is_vertical)
		wall_x = cray.ray.hit.y - floor(cray.ray.hit.y / TILESIZE) * TILESIZE;
	else
		wall_x = cray.ray.hit.x - floor(cray.ray.hit.x / TILESIZE) * TILESIZE;
	offset.x = (int)((wall_x / TILESIZE) * cray.tex.width);
	st_y = (HEIGHT - cray.slice_hieght) / 2;
	while (top < bottom)
	{
		offset.y = (int)(((top - st_y) / cray.slice_hieght) * cray.tex.height);
		put_pixel(game, (t_xy){cray.ray_num, top},
			shade_color(get_pixel_color(cray.tex, offset), cray.dist));
		top++;
	}
}

static inline void	draw_slice(t_game *game,
	t_ray ray, float ray_angle, int ray_num)
{
	t_casted_ray	cray;

	cray.dist = distance(game->player.pos, ray.hit)
		* cos(ray_angle - game->player.angle);
	cray.slice_hieght = (TILESIZE / cray.dist)
		* ((WIDTH / 2) / tan(FOV * PI / 360));
	cray.ray_num = ray_num;
	cray.ray = ray;
	cray.wall_top = (HEIGHT - cray.slice_hieght) / 2;
	cray.wall_bottom = cray.wall_top + cray.slice_hieght;
	if (cray.wall_top < 0)
		cray.wall_top = 0;
	if (cray.wall_bottom >= HEIGHT)
		cray.wall_bottom = HEIGHT - 1;
	cray.tex = game->scene.textures.door;
	if (ray.dir == NORTH)
		cray.tex = game->scene.textures.north;
	else if (ray.dir == SOUTH)
		cray.tex = game->scene.textures.south;
	else if (ray.dir == EAST)
		cray.tex = game->scene.textures.east;
	else if (ray.dir == WEST)
		cray.tex = game->scene.textures.west;
	draw_tex_slice(game, cray, cray.wall_bottom, cray.wall_top);
}

inline void	draw_textured(t_game *game)
{
	t_ray	ray;
	float	ray_angle;
	float	s_angle;
	float	angle_step;
	int		i;

	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, game->scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2, WIDTH,
		game->scene.floor_color);
	i = 0;
	s_angle = game->player.angle - (FOV * PI / 180) / 2;
	angle_step = (FOV * PI / 180) / game->n_rays;
	while (i < game->n_rays)
	{
		ray_angle = s_angle + i * angle_step;
		ray = cast_ray(ray_angle);
		draw_slice(game, ray, ray_angle, i);
		i++;
	}
}
