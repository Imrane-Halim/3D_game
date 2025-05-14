/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:15:59 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 11:02:50 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	player_collision(t_game *game, t_xy new_pos)
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
		if (obj_hit(game, tmp) != '0'
			&& obj_hit(game, tmp) != 'O')
			return (true);
		angle += PI / 4;
	}
	return (false);
}

t_xy	check_collison(t_game *game, t_xy new_pos)
{
	t_xy	tmp_pos;

	tmp_pos = new_pos;
	tmp_pos.x = game->player.pos.x;
	if (!player_collision(game, tmp_pos))
		return (tmp_pos);
	tmp_pos = new_pos;
	tmp_pos.y = game->player.pos.y;
	if (!player_collision(game, tmp_pos))
		return (tmp_pos);
	return (game->player.pos);
}

t_xy	unstick_player(t_game *game, t_xy pos)
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
		if (!player_collision(game, test_pos))
			return (test_pos);
		angle += PI / 4;
	}
	return (pos);
}

void	ch_player_pos(t_game *game, int dir, bool is_strafe)
{
	t_xy	new_pos;
	float	move_angle;

	if (player_collision(game, game->player.pos))
		game->player.pos = unstick_player(game, game->player.pos);
	if (is_strafe)
		move_angle = game->player.angle + (dir * PI / 2);
	else
		move_angle = game->player.angle;
	if (dir == BACKWARD && !is_strafe)
		move_angle += PI;
	new_pos.x = game->player.pos.x + cos(move_angle) * POS_STEP;
	new_pos.y = game->player.pos.y + sin(move_angle) * POS_STEP;
	if (player_collision(game, new_pos))
	{
		new_pos = check_collison(game, new_pos);
		if (player_collision(game, new_pos))
			return ;
	}
	game->player.pos = new_pos;
}

void	ch_player_xangle(t_game *game, float angle)
{
	float	new_angle;

	new_angle = game->player.angle + angle;
	if (fabs(new_angle) > PI * 2)
		new_angle = 0;
	game->player.angle = new_angle;
}
