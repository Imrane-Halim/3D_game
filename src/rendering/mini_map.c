#include "cub3d.h"

#define MIN_TILZESIZE 10
// MIN_TILZESIZE / TILESIZE
#define SCALE 0.15625
#define BOUND_CLR 0x00ff00
#define BOUND_THIK 9

// static t_xy	get_camera_offset(void)
// {
// 	t_xy	offset;

// 	offset.x = g_game.minimap.width / 2 - g_game.player.pos.x * SCALE;
// 	offset.y = g_game.minimap.height / 2 - g_game.player.pos.y * SCALE;
// 	return (offset);
// }

static t_xy	applay_offset(t_xy pos, t_xy offset)
{
	return ((t_xy){pos.x + offset.x + g_game.minimap.pos.x, pos.y + offset.y
		+ g_game.minimap.pos.y});
}

static inline void	draw_tile(t_xy pos, t_xy offset, int color)
{
	t_xy	m_pos;

	m_pos = g_game.minimap.pos;
	pos = applay_offset(pos, offset);
	if (pos.x >= m_pos.x && pos.x <= m_pos.x + g_game.minimap.width
		&& pos.y >= m_pos.y && pos.y <= m_pos.y + g_game.minimap.height)
		draw_square(pos, MIN_TILZESIZE, MIN_TILZESIZE, color);
}

static inline void	draw_map(t_xy offset)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = 0;
	while (g_game.scene.map[y])
	{
		x = 0;
		while (g_game.scene.map[y][x])
		{
			if (g_game.scene.map[y][x] == '1')
				color = g_game.minimap.wall_color;
			else if (g_game.scene.map[y][x] == 'D'
				|| g_game.scene.map[y][x] == 'O')
				color = g_game.minimap.door_color;
			else
				color = g_game.minimap.floor_color;
			draw_tile((t_xy){x * MIN_TILZESIZE, y * MIN_TILZESIZE}, offset,
				color);
			x++;
		}
		y++;
	}
}

// static void	draw_player(t_xy offset)
// {
// 	t_xy	pos;

// 	pos.x = g_game.player.pos.x * SCALE;
// 	pos.y = g_game.player.pos.y * SCALE;
// 	pos = applay_offset(pos, offset);
// 	pos.x -= 2;
// 	pos.y -= 2;
// 	draw_square(pos, 5, 5, 0xe60b3e);
// }

void	draw_dir(t_xy offset)
{
	t_xy	start;
	t_xy	pos;
	t_xy	end;
	float	line_lenght;

	line_lenght = 50;
	pos.x = g_game.player.pos.x * SCALE;
	pos.y = g_game.player.pos.y * SCALE;
	start = applay_offset(pos, offset);
	end.x = pos.x + cos(g_game.player.angle) * line_lenght;
	end.y = pos.y + sin(g_game.player.angle) * line_lenght;
	end = applay_offset(end, offset);
	draw_line(start, end, 0xe60b3e);
}

// this function used to be clear and readable but
// I had to remove some helper functions and put their code here
// because of the norme, old implementation is in the comments
inline void	draw_minimap(void)
{
	t_xy	offset;
	t_xy	pos;

	offset.x = g_game.minimap.width / 2 - g_game.player.pos.x * SCALE;
	offset.y = g_game.minimap.height / 2 - g_game.player.pos.y * SCALE;
	draw_square(g_game.minimap.pos, g_game.minimap.height, g_game.minimap.width,
		g_game.minimap.floor_color);
	draw_map(offset);
	pos.x = g_game.player.pos.x * SCALE;
	pos.y = g_game.player.pos.y * SCALE;
	pos = applay_offset(pos, offset);
	pos.x -= 2;
	pos.y -= 2;
	draw_square(pos, 5, 5, 0xe60b3e);
	draw_dir(offset);
	pos = g_game.minimap.pos;
	draw_square(pos, BOUND_THIK, g_game.minimap.width, BOUND_CLR);
	pos.x += g_game.minimap.width;
	draw_square(pos, g_game.minimap.height + BOUND_THIK, BOUND_THIK, BOUND_CLR);
	pos.x -= g_game.minimap.width;
	draw_square(pos, g_game.minimap.height, BOUND_THIK, BOUND_CLR);
	pos.y += g_game.minimap.height;
	draw_square(pos, BOUND_THIK, g_game.minimap.width, BOUND_CLR);
}

// void	draw_bounds()
// {
// 	t_xy	pos = g_game.minimap.pos;

// 	// draw top bar
// 	draw_square(pos, BOUND_THIk, g_game.minimap.width, BOUND_CLR);

// 	// draw right bar
// 	pos.x += g_game.minimap.width;
// 	draw_square(pos, g_game.minimap.height + BOUND_THIk, BOUND_THIk, BOUND_CLR);

// 	// draw left bar
// 	pos.x -= g_game.minimap.width;
// 	draw_square(pos, g_game.minimap.height, BOUND_THIk, BOUND_CLR);

// 	// draw bottom bar
// 	pos.y += g_game.minimap.height;
// 	draw_square(pos, BOUND_THIk, g_game.minimap.width, BOUND_CLR);
// }

// inline void	draw_minimap()
// {
// 	t_xy	offset = get_camera_offset();

// 	// background
// 	draw_square(g_game.minimap.pos, g_game.minimap.height,
// 		g_game.minimap.width, g_game.minimap.floor_color);

// 	// drawing walls
// 	draw_map(offset);

// 	draw_player(offset);

// 	draw_dir(offset);

// 	// hide some unwanted stuff in the map edges
// 	draw_bounds();
// }