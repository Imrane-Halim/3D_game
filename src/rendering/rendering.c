#include "cub3d.h"

void	put_pixel(t_coordinates coord, int color)
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

void	draw_square(t_coordinates coord, int height, int width, int color)
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

void	draw_line(t_coordinates start, t_coordinates end, int color)
{
	int				dx;
	int				dy;
	int				step;
	t_coordinates	incr;
	t_coordinates	cord;

	dx = (int)end.x - (int)start.x;
	dy = (int)end.y - (int)start.y;
	step = abs(dy);
	if (abs(dx) > abs(dy))
		step = abs(dx);
	incr.x = (float)dx / step;
	incr.y = (float)dy / step;
	cord.x = start.x;
	cord.y = start.y;
	for (int i = 0; i < step; i++)
	{
		put_pixel(cord, color);
		cord.x += incr.x;
		cord.y += incr.y;
	}
}
// ------------------------- 2D helpers
void	draw_map(void)
{
	char	**map;
	int		x;
	int		y;

	map = g_game.scene.map;
	y = 0;
	while (y < g_game.scene.m_height)
	{
		x = 0;
		while (x < g_game.scene.m_width)
		{
			if (map[y][x] == '1')
				draw_square((t_coordinates){x * TILESIZE, y * TILESIZE},
					TILESIZE, TILESIZE, 0xffffff);
			x++;
		}
		y++;
	}
}

void	draw_player(void)
{
	int	endx;
	int	endy;
	int	line_lenght;

	line_lenght = 100;
	// draw player square
	draw_square(g_game.player.pos, 16, 16, 0xf2a200);
	// draw player looking direction
	endx = (int)g_game.player.pos.x + cos(g_game.player.angle) * line_lenght;
	endy = (int)g_game.player.pos.y + sin(g_game.player.angle) * line_lenght;
	draw_line(g_game.player.pos, (t_coordinates){endx, endy}, 0xff0000);
}

//--------------------------

void	draw_2D_view(void)
{
	draw_square((t_coordinates){0, 0}, HEIGHT, WIDTH, 0x2e2d2d);
	draw_map();
	draw_player();
}
// void	draw_3D_view(void)
//{}

//-----------------------

int	render_frame(void)
{
	draw_2D_view();
	// draw_3D_view();
	mlx_put_image_to_window(g_game.window.mlx, g_game.window.win,
		g_game.window.frame.img, 0, 0);
	return (0);
}