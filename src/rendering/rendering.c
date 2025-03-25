/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:47 by imrane            #+#    #+#             */
/*   Updated: 2025/03/25 19:21:48 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// # define __DEBUG__	false

inline void	put_pixel(t_xy coord, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)coord.x;
	y = (int)coord.y;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = g_game.window.frame.adr + (y * g_game.window.frame.line_length + x
			* (g_game.window.frame.bbp / 8));
	*(unsigned int *)dst = color;
}

//-------------------------- some core stuff

inline void	draw_square(t_xy coord, int height, int width, int color)
{
	int	save_x;
	int	save_y;

	save_x = coord.x;
	save_y = coord.y;
	while (coord.y < height + save_y)
	{
		coord.x = save_x;
		while (coord.x < width + save_x)
		{
			put_pixel(coord, color);
			coord.x++;
		}
		coord.y++;
	}
}

inline void	draw_line(t_xy start, t_xy end, int color)
{
	float	dx;
	float	dy;
	float	step;
	t_xy	coord;
	int		i;

	step = fmax(fabs(end.x - start.x), fabs(end.y - start.y));
	dx = (end.x - start.x) / step;
	dy = (end.y - start.y) / step;
	coord = start;
	i = 0;
	while (i <= step)
	{
		put_pixel(coord, color);
		coord.x += dx;
		coord.y += dy;
		i++;
	}
}

//-----------------------

static void	draw_hand(void)
{
	t_xy			pos;
	int				hand_y;
	static int		old_y = HEIGHT / 2;
	unsigned int	color;

	hand_y = (HEIGHT / 2) + (int)(cos(g_game.timer * 0.05f) * 100);
	if (g_game.key.w || g_game.key.s || g_game.key.d || g_game.key.a)
		old_y = hand_y;
	pos.y = -1;
	while (++pos.y < g_game.hand.height)
	{
		pos.x = -1;
		while (++pos.x < g_game.hand.width)
		{
			color = get_pixel_color(g_game.hand, pos);
			if (color != 0xff000000)
				put_pixel((t_xy){pos.x + (WIDTH - g_game.hand.width), pos.y
					+ old_y}, color);
		}
	}
}

inline int	render_frame(void)
{
	draw_textured();
	draw_minimap();
	draw_hand();
	mlx_put_image_to_window(g_game.window.mlx, g_game.window.win,
		g_game.window.frame.img, 0, 0);
	return (0);
}
