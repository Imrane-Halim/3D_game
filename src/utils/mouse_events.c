/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:16:08 by imrane            #+#    #+#             */
/*   Updated: 2025/05/10 14:35:05 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_input(int x, int y, void *data)
{
	int			dx;
	t_game		*game;
	static int	center_x = WIDTH / 2;
	static int	center_y = HEIGHT / 2;

	game = (t_game *)data;
	dx = x - center_x;
	game->player.angle += dx * MOUSE_SENS;
	if (x != center_x || y != center_y)
		mlx_mouse_move(game->window.mlx, game->window.win,
			center_x, center_y);
	return (0);
}
