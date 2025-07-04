/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:47 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 16:24:29 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline void	put_pixel(t_game *game, t_xy coord, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)coord.x;
	y = (int)coord.y;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = game->window.frame.adr
		+ (y * game->window.frame.line_length + x
			* (game->window.frame.bbp / 8));
	*(unsigned int *)dst = color;
}

//-------------------------- some core stuff

inline void	draw_square(t_xy coord, int height, int width, int color)
{
	int		save_x;
	int		save_y;
	t_game	*game;

	game = g_game();
	save_x = coord.x;
	save_y = coord.y;
	while (coord.y < height + save_y)
	{
		coord.x = save_x;
		while (coord.x < width + save_x)
		{
			put_pixel(game, coord, color);
			coord.x++;
		}
		coord.y++;
	}
}

inline void	draw_line(t_game *game, t_xy start, t_xy end, int color)
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
		put_pixel(game, coord, color);
		coord.x += dx;
		coord.y += dy;
		i++;
	}
}

//-----------------------

static inline void	draw_hand(t_game *game)
{
	t_xy			pos;
	int				hand_y;
	unsigned int	color;
	static float	speed = 0.03f;
	static int		power = 100;

	hand_y = (HEIGHT / 2) + (int)(cos(game->timer * speed) * power);
	pos.y = -1;
	while (++pos.y < game->hand.height)
	{
		pos.x = -1;
		while (++pos.x < game->hand.width)
		{
			color = get_pixel_color(game->hand, pos);
			if (color != 0xff000000)
				put_pixel(game, (t_xy){pos.x + (WIDTH - game->hand.width), pos.y
					+ hand_y}, color);
		}
	}
}

inline int	render_frame(t_game *game)
{
	draw_textured(game);
	// draw_2D_view();
	// draw_3D_view();
	draw_minimap(game);
	draw_hand(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->window.frame.img, 0, 0);
	return (0);
}
