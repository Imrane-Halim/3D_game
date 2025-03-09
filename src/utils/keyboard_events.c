#include "cub3d.h"

void ch_player_pos(int dir, bool is_strafe)
{
	float new_x;
	float new_y;
	
	new_x = g_game.player.pos.x + cos(g_game.player.angle) * dir * POS_STEP;
	new_y = g_game.player.pos.y + sin(g_game.player.angle) * dir * POS_STEP;
	if (is_strafe)
	{
		float strafe_angle = g_game.player.angle + (dir * PI / 2);
		new_x = g_game.player.pos.x + cos(strafe_angle) * POS_STEP;
		new_y = g_game.player.pos.y + sin(strafe_angle) * POS_STEP;
	}

	if (new_x < 0 || new_x >= WIDTH)
		return;
	if (new_y < 0 || new_y >= HEIGHT)
		return;
	
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
		g_game.key.up = is_pressed;
	else if (keynum == DOWN_KEY)
		g_game.key.down = is_pressed;
	else if (keynum == RIGHT_KEY)
		g_game.key.right = is_pressed;
	else if (keynum == LEFT_KEY)
		g_game.key.left = is_pressed;
	else if (keynum == A_KEY)
		g_game.key.a = is_pressed;
	else if (keynum == D_KEY)
		g_game.key.d = is_pressed;
	else if (keynum == S_KEY)
		g_game.key.s = is_pressed;
	else if (keynum == W_KEY)
		g_game.key.w = is_pressed;
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
	if (g_game.key.w)
		ch_player_pos(FORWARD, false);
	if (g_game.key.s)
		ch_player_pos(BACKWARD, false);
	if (g_game.key.d)
		ch_player_pos(FORWARD, true);
	if (g_game.key.a)
		ch_player_pos(BACKWARD, true);
	if (g_game.key.right)
		ch_player_xangle(AGL_STEP);
	if (g_game.key.left)
		ch_player_xangle(-AGL_STEP);
	return (0);
}
