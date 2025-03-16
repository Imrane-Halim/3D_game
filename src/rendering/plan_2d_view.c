#include "cub3d.h"

static t_xy	get_camera_offset()
{
	t_xy	offset;

	offset.x = WIDTH / 2 - g_game.player.pos.x;
	offset.y = HEIGHT / 2 - g_game.player.pos.y;

	return (offset);
}

static t_xy	applay_offset(t_xy pos, t_xy offset)
{
	return ((t_xy){pos.x + offset.x, pos.y + offset.y});
}

static void	draw_background()
{
	int	i;

	// background
	draw_square((t_xy){0, 0}, HEIGHT, WIDTH, 0x262626);
	
	// horizontal grid
	i = 0;
	while (i < HEIGHT)
	{
		draw_line((t_xy){0, i}, (t_xy){WIDTH, i}, 0x333333);
		i += TILESIZE;
	}

	// vertical grid
	i = 0;
	while (i < WIDTH)
	{
		draw_line((t_xy){i, 0}, (t_xy){i, HEIGHT}, 0x333333);
		i += TILESIZE;
	}
}

static void	draw_map(t_xy offset)
{
	int		x;
	int		y;
	t_xy	pos;
	
	y = 0;
	while (g_game.scene.map[y])
	{
		x = 0;
		while (g_game.scene.map[y][x])
		{
			if (g_game.scene.map[y][x] == '1')
			{
				pos.y = y * TILESIZE;
				pos.x = x * TILESIZE;
				pos = applay_offset(pos, offset);
				draw_square(pos, TILESIZE, TILESIZE, 0xffffff);
			}
			x++;
		}
		y++;
	}
}

static void	draw_player(t_xy offset)
{
	t_xy	pos;

	pos = applay_offset(g_game.player.pos, offset);
	pos.x -= 8;
	pos.y -= 8;
	draw_square(pos, 16, 16, 0xe60b3e);
}

static void	draw_fov(t_xy offset)
{
	t_xy	start;
	t_xy	end;

	float	step;
	float	s_angle;
	float	e_angle;

	s_angle = g_game.player.angle - (FOV * PI / 180) / 2;
	e_angle = g_game.player.angle + (FOV * PI / 180) / 2;
	// step = (FOV * PI / 180) / g_game.n_rays;
	step = 0.001;
	while (s_angle < e_angle)
	{
		start = applay_offset(g_game.player.pos, offset);
		end = applay_offset(cast_ray(s_angle), offset);
		draw_line(start, end, 0x02cf0c);
		s_angle += step;
	}
}

static void	draw_dir(t_xy offset)
{
	t_xy	start;
	t_xy	end;

	float	line_lenght;

	line_lenght = 100;
	start = applay_offset(g_game.player.pos, offset);
	end.x = g_game.player.pos.x + cos(g_game.player.angle) * line_lenght;
	end.y = g_game.player.pos.y + sin(g_game.player.angle) * line_lenght;
	end = applay_offset(end, offset);
	draw_line(start, end, 0xe60b3e);
}

inline void	draw_2D_view(void)
{
	t_xy	offset;

	offset = get_camera_offset();
	draw_background();
	draw_map(offset);
	draw_player(offset);
	draw_fov(offset);
	draw_dir(offset);
}
