/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:15:59 by imrane            #+#    #+#             */
/*   Updated: 2025/03/27 21:28:01 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	player_collision(t_xy new_pos)
{
	float	radius;
	float	angle;
	t_xy	tmp;

	radius = TILESIZE * 0.1;
	angle = 0;
	while (angle < PI * 2)
	{
		tmp.x = new_pos.x + cos(angle) * radius;
		tmp.y = new_pos.y + sin(angle) * radius;
		if (obj_hit(tmp) != '0' && obj_hit(tmp) != 'O')
			return (true);
		angle += PI / 4;
	}
	return (false);
}

t_xy	check_collison(t_xy new_pos)
{
	t_xy	tmp_pos;

	tmp_pos = new_pos;
	tmp_pos.x = g_game()->player.pos.x;
	if (!player_collision(tmp_pos))
		return (tmp_pos);
	tmp_pos = new_pos;
	tmp_pos.y = g_game()->player.pos.y;
	if (!player_collision(tmp_pos))
		return (tmp_pos);
	return (g_game()->player.pos);
}

t_xy	unstick_player(t_xy pos)
{
	t_xy	test_pos;
	float	angle;
	float	radius;

	angle = 0;
	radius = TILESIZE * 0.15;
	while (angle < PI * 2)
	{
		test_pos.x = pos.x + cos(angle) * radius;
		test_pos.y = pos.y + sin(angle) * radius;
		if (!player_collision(test_pos))
			return (test_pos);
		angle += PI / 4;
	}
	return (pos);
}

void	ch_player_pos(int dir, bool is_strafe)
{
	t_xy	new_pos;
	float	move_angle;

	if (player_collision(g_game()->player.pos))
		g_game()->player.pos = unstick_player(g_game()->player.pos);
	if (is_strafe)
		move_angle = g_game()->player.angle + (dir * PI / 2);
	else
		move_angle = g_game()->player.angle;
	if (dir == BACKWARD && !is_strafe)
		move_angle += PI;
	new_pos.x = g_game()->player.pos.x + cos(move_angle) * POS_STEP;
	new_pos.y = g_game()->player.pos.y + sin(move_angle) * POS_STEP;
	if (player_collision(new_pos))
	{
		new_pos = check_collison(new_pos);
		if (player_collision(new_pos))
			return ;
	}
	g_game()->player.pos = new_pos;
}

void	ch_player_xangle(float angle)
{
	float	new_angle;

	new_angle = g_game()->player.angle + angle;
	if (fabs(new_angle) > PI * 2)
		new_angle = 0;
	g_game()->player.angle = new_angle;
}
