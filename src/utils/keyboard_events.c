#include "cub3d.h"

// note: angle is an radina

t_xy	check_collison(t_xy new_pos)
{
	t_xy tmp_pos = new_pos;

	tmp_pos.x = g_game.player.pos.x;
	if (obj_hit(tmp_pos) == '0')
		return (tmp_pos);
	tmp_pos = new_pos;
	tmp_pos.y = g_game.player.pos.y;
	if (obj_hit(tmp_pos) == '0')
		return (tmp_pos);
	return (g_game.player.pos);
}

void ch_player_pos(int dir, bool is_strafe)
{
	t_xy	new_pos;
	float	move_angle;

	if (is_strafe)
		move_angle = g_game.player.angle + (dir * PI / 2);
	else
	{
		move_angle = g_game.player.angle;
		if (dir == BACKWARD)
			move_angle += PI;
	}
	new_pos.x = g_game.player.pos.x + cos(move_angle) * POS_STEP;
	new_pos.y = g_game.player.pos.y + sin(move_angle) * POS_STEP;
	if (obj_hit(new_pos) != '0')
		new_pos	= check_collison(new_pos);
	g_game.player.pos = new_pos;
}

void	ch_player_xangle(float angle)
{
	float new_angle;
	
	new_angle = g_game.player.angle + angle;
	if (fabs(new_angle) > PI * 2)
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
	if (g_game.timer < 13)
		return 0;
	g_game.timer = 0;
	if (g_game.key.w || g_game.key.up)
		ch_player_pos(FORWARD, false);
	if (g_game.key.s || g_game.key.down)
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
