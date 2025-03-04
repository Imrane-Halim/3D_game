#include "cub3d.h"

void	init_window()
{
	g_game.window.mlx = mlx_init();
	g_game.window.win = mlx_new_window(g_game.window.mlx, WIDTH, HEIGHT, TITLE);
	g_game.window.frame.img = mlx_new_image(g_game.window.mlx, WIDTH, HEIGHT);
	g_game.window.frame.adr = mlx_get_data_addr(g_game.window.frame.img, 
		&g_game.window.frame.bbp, &g_game.window.frame.line_length, &g_game.window.frame.endian);
}

void	init_player()
{
	// convert degree to radian
	g_game.player.fov = 60 * (PI / 180);
	g_game.player.pos.x = 64;
	g_game.player.pos.y = 64;
	g_game.player.angle.x = 0;
	// angle.y will be used to control pov with mouse
	g_game.player.angle.y = 0;
}

void	init_game()
{
	init_window();
	init_player();
	// todo:
	// g_game.scene = parse_map(av[1]);
	static char *map[] = 
	{
		"111111111111111111111111",
		"100000100000000100000001",
		"100000000000000100000001",
		"100000000000000100000001",
		"100000000000000100000001",
		"100000111111111100000001",
		"100000000000000100000001",
		"100000000000000000000001",
		"100010000000000000000001",
		"100010000000000000000001",
		"100010000000000000000001",
		"100010000000000000000001",
		"111111111111111111111111"
	};
	g_game.scene.map = map;
	g_game.scene.m_width = 24;
	g_game.scene.m_height = 13;
}
