#include "cub3d.h"

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
				draw_square((t_xy){x * TILESIZE, y * TILESIZE},
					TILESIZE, TILESIZE, 0xffffff);
			x++;
		}
		y++;
	}
}

// note: player angle is radian
// FOV in degrees
void draw_fov()
{
	t_xy	ray;
	
	float	half = (FOV * PI / 180) / 2;
	float	s_angle = g_game.player.angle - half;
	float	e_angle = g_game.player.angle + half;
	
	float	step = (e_angle - s_angle) / g_game.n_rays;
	while (s_angle < e_angle)
	{
		ray = cast_ray(s_angle);
		draw_line(g_game.player.pos, ray, 0x00ff00);
		s_angle += step;
	}
}

void	draw_player(void)
{
	int	endx;
	int	endy;

	int startx;
	int starty;

	int	line_lenght;

	line_lenght = 100;
	
	startx = (int)g_game.player.pos.x;
	starty = (int)g_game.player.pos.y;

	// draw player square
	draw_square((t_xy){startx - 8, starty - 8}, 16, 16, 0xf2a200);
	
	// draw fov
	draw_fov();

	// draw player looking direction

	endx = startx + cos(g_game.player.angle) * line_lenght;
	endy = starty + sin(g_game.player.angle) * line_lenght;

	draw_line((t_xy){startx, starty}, (t_xy){endx, endy}, 0xff0000);
}

//--------------------------

void	draw_2D_view(void)
{
	// gray background
	draw_square((t_xy){0, 0}, HEIGHT, WIDTH, 0x2e2d2d);

	// draw map walls
	draw_map();

	// draw curr pos of player in map + looking direction
	draw_player();

}
