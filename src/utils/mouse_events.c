/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:16:08 by imrane            #+#    #+#             */
/*   Updated: 2025/03/25 19:16:38 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_input(int x, int y, void *data)
{
	int	dx;

	(void)data;
	(void)y;
	dx = x - (WIDTH / 2);
	g_game.player.angle += dx * MOUSE_SENS;
	if (g_game.player.angle > 2 * PI)
		g_game.player.angle = 0;
	mlx_mouse_move(g_game.window.mlx, g_game.window.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
