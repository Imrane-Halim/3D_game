/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:16:08 by imrane            #+#    #+#             */
/*   Updated: 2025/05/10 10:12:13 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_input(int x, int y, void *data)
{
	int		dx;
	t_game	*game;

	(void)y;
	game = (t_game *)data;
	dx = x - (WIDTH / 2);
	game->player.angle += dx * MOUSE_SENS;
	if (game->player.angle > 2 * PI)
		game->player.angle = 0;
	mlx_mouse_move(game->window.mlx,
		game->window.win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
