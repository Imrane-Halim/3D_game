#include "cub3d.h"

// if dir = 1: move forward
// if dir = -1: move backward
void	ch_player_pos(int dir)
{
	float	new_x;
	float	new_y;

	new_x = g_game.player.pos.x + cos(g_game.player.angle) * dir * POS_STEP;
	new_y = g_game.player.pos.y + sin(g_game.player.angle) * dir * POS_STEP;

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
	
	new_angle = g_game.player.angle + angle;
	if (fabs(new_angle) > 6.24)
		new_angle = 0;
	g_game.player.angle = new_angle;
}

int 	handle_key(int keynum, bool is_pressed)
{
	if (keynum == ESC_KEY && is_pressed)
		close_game(0);
	else if (keynum == UP_KEY)
		g_game.player.up = is_pressed;
	else if (keynum == DOWN_KEY)
		g_game.player.down = is_pressed;
	else if (keynum == RIGHT_KEY)
		g_game.player.right = is_pressed;
	else if (keynum == LEFT_KEY)
		g_game.player.left = is_pressed;
	return 0;
}

int 	handle_press(int keynum)
{
	return handle_key(keynum, true);
}

int 	handle_release(int keynum)
{
	return handle_key(keynum, false);
}

int		Keyboard_input()
{
	if (g_game.timer < 6)
		return 0;
	g_game.timer = 0;
	if (g_game.player.up)
		ch_player_pos(1);
	if (g_game.player.down)
		ch_player_pos(-1);
	if (g_game.player.right)
		ch_player_xangle(AGL_STEP);
	if (g_game.player.left)
		ch_player_xangle(-AGL_STEP);
	return (0);
}
