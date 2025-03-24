#include "cub3d.h"

# define __DEBUG__	false

inline void	put_pixel(t_xy coord, int color)
{
	char	*dst;
	int		x;
	int		y;

	x = (int)coord.x;
	y = (int)coord.y;
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = g_game.window.frame.adr
			+ (y * g_game.window.frame.line_length
			+ x * (g_game.window.frame.bbp / 8));
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

inline void draw_line(t_xy start, t_xy end, int color)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float step = fmax(fabs(dx), fabs(dy));
	
	dx /= step;
	dy /= step;
	
	float x = start.x;
	float y = start.y;
	
	for (int i = 0; i <= step; i++)
	{
		put_pixel((t_xy){x, y}, color);
		x += dx;
		y += dy;
	}
}

//-----------------------

static void	draw_hand()
{
	float speed = 0.05f;
	int amplitude = 100;
	static int	old_y = HEIGHT / 2;

	int hand_y = (HEIGHT / 2) + (int)(cos(g_game.timer * speed) * amplitude);
	if (g_game.key.w || g_game.key.s)
		old_y = hand_y;
	
	int hand_x = WIDTH - g_game.hand.width;
	unsigned int color = 0;

	for (int y = 0; y < g_game.hand.height; y++)
	{
		for (int x = 0; x < g_game.hand.width; x++)
		{
			color = get_pixel_color(g_game.hand, (t_xy){x, y});
			if (color != 0xFF000000) // Skip transparent pixels
				put_pixel((t_xy){x + hand_x, y + old_y}, color);
		}
	}
}

inline int	render_frame(void)
{
#if __DEBUG__
	// draw_2D_view();
	draw_3D_view();
#else
	draw_textured();
#endif
	draw_minimap();
	draw_hand();
	mlx_put_image_to_window(g_game.window.mlx, g_game.window.win,
		g_game.window.frame.img, 0, 0);
	return (0);
}