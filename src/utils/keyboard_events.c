#include "cub3d.h"

int 	handle_key(int keynum, bool is_pressed)
{
	if (keynum == ESC_KEY && is_pressed)
		close_game(0, NULL);
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

void	door_event()
{
	float	x, y;
	float	radius;
	char	c;

	radius = TILESIZE;
	x = g_game.player.pos.x + cos(g_game.player.angle) * radius;
	y = g_game.player.pos.y + sin(g_game.player.angle) * radius;
	c = obj_hit((t_xy){x, y});
	if (c != 'D' && c != 'O')
		return ;
	if (c == 'D')
		g_game.scene.map[(int)y / TILESIZE][(int)x / TILESIZE] = 'O';
	else
		g_game.scene.map[(int)y / TILESIZE][(int)x / TILESIZE] = 'D';
}

int 	handle_press(int keynum)
{
	if (keynum == ' ')
		door_event();
	return handle_key(keynum, true);
}

int 	handle_release(int keynum)
{
	return handle_key(keynum, false);
}

int		Keyboard_input()
{
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
