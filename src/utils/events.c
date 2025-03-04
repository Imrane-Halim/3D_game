#include "cub3d.h"

// if dir = 1: move forward
// if dir = -1: move backward
void	move_player(int dir)
{
	int	new_x;
	int	new_y;

	new_x = g_game.player.pos.x + cos(g_game.player.angle.x) * dir * 16;
	new_y = g_game.player.pos.y + sin(g_game.player.angle.x) * dir * 16;

	if (new_x < 0 || new_x >= WIDTH)
		return ;
	if (new_y < 0 || new_y >= HEIGHT)
		return ;
	
	g_game.player.pos.x = new_x;
	g_game.player.pos.y = new_y;
}

int		Keyboard_input(int keynum)
{
	if (keynum == ESC_KEY)
		close_game(0);
	if (keynum == UP_KEY)
		move_player(1);
	if (keynum == DOWN_KEY)
		move_player(-1);
	if (keynum == RIGHT_KEY)
		g_game.player.angle.x -= 0.1;
	if (keynum == LEFT_KEY)
		g_game.player.angle.x += 0.1;
	return (0);
}
