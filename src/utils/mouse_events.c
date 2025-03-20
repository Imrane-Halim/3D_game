#include "cub3d.h"

int Mouse_input(int x, int y, void *data)
{
	(void)data;
	(void)y;

	int		dx;

	dx = x - (WIDTH / 2);
	g_game.player.angle += dx * MOUSE_SENS;
	if (g_game.player.angle > 2 * PI)
		g_game.player.angle = 0;
	mlx_mouse_move(g_game.window.mlx, g_game.window.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
