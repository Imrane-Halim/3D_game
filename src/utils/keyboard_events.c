/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:16:58 by imrane            #+#    #+#             */
/*   Updated: 2025/05/10 09:31:45 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key(t_game *game, int keynum, bool is_pressed)
{
	if (keynum == ESC_KEY && is_pressed)
		close_game(0, NULL);
	else if (keynum == UP_KEY)
		game->key.up = is_pressed;
	else if (keynum == DOWN_KEY)
		game->key.down = is_pressed;
	else if (keynum == RIGHT_KEY)
		game->key.right = is_pressed;
	else if (keynum == LEFT_KEY)
		game->key.left = is_pressed;
	else if (keynum == A_KEY)
		game->key.a = is_pressed;
	else if (keynum == D_KEY)
		game->key.d = is_pressed;
	else if (keynum == S_KEY)
		game->key.s = is_pressed;
	else if (keynum == W_KEY)
		game->key.w = is_pressed;
	return (0);
}

void	door_event(t_game *game)
{
	float	radius;
	char	c;
	float	x;
	float	y;

	radius = TILESIZE;
	x = game->player.pos.x + cos(game->player.angle) * radius;
	y = game->player.pos.y + sin(game->player.angle) * radius;
	c = obj_hit((t_xy){x, y});
	if (c != 'D' && c != 'O')
		return ;
	if (c == 'D')
		game->scene.map[(int)y / TILESIZE][(int)x / TILESIZE] = 'O';
	else
		game->scene.map[(int)y / TILESIZE][(int)x / TILESIZE] = 'D';
}

int	handle_press(int keynum)
{
	if (keynum == ' ')
		door_event(g_game());
	return (handle_key(g_game(), keynum, true));
}

int	handle_release(int keynum)
{
	return (handle_key(g_game(), keynum, false));
}

int	keyboard_input(t_game *game)
{
	if (game->key.w || game->key.up)
		ch_player_pos(game, FORWARD, false);
	if (game->key.s || game->key.down)
		ch_player_pos(game, BACKWARD, false);
	if (game->key.d)
		ch_player_pos(game, FORWARD, true);
	if (game->key.a)
		ch_player_pos(game, BACKWARD, true);
	if (game->key.right)
		ch_player_xangle(game, AGL_STEP);
	if (game->key.left)
		ch_player_xangle(game, -AGL_STEP);
	return (0);
}
