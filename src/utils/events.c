#include "cub3d.h"

// if dir = 1: move forward
// if dir = -1: move backward
void	ch_player_pos(int dir)
{
	float	new_x;
	float	new_y;

	new_x = g_game.player.pos.x + cos(g_game.player.angle.x) * dir * 16;
	new_y = g_game.player.pos.y + sin(g_game.player.angle.x) * dir * 16;

	if (new_x < 0 || new_x >= WIDTH)
		return ;
	if (new_y < 0 || new_y >= HEIGHT)
		return ;
	
	g_game.player.pos.x = new_x;
	g_game.player.pos.y = new_y;
}

void	ch_player_xangle(float angle)
{
	float new_angle;
	
	new_angle = g_game.player.angle.x + angle;
	if (fabs(new_angle) > 6.24)
		new_angle = 0;
	g_game.player.angle.x = new_angle;
}

int		Keyboard_input(int keynum)
{
	if (keynum == ESC_KEY)
		close_game(0);
	if (keynum == UP_KEY)
		ch_player_pos(1);
	if (keynum == DOWN_KEY)
		ch_player_pos(-1);
	if (keynum == RIGHT_KEY)
		ch_player_xangle(0.1);
	if (keynum == LEFT_KEY)
		ch_player_xangle(-0.1);
	return (0);
}
