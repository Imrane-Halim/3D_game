/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:11:00 by ihalim            #+#    #+#             */
/*   Updated: 2025/05/14 11:00:39 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline t_game	*g_game(void)
{
	static t_game	game;

	return (&game);
}

void	init_game(void)
{
	g_game()->n_rays = WIDTH;
	init_window();
	init_textures();
	init_minimap();
}

int	game_loop(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	game->timer++;
	keyboard_input(game);
	render_frame(game);
	return (0);
}

// mlx_hide_mouse()
void	start_game(void)
{
	t_game	*game;

	game = g_game();
	mlx_hook(game->window.win, KeyPress, KeyPressMask, handle_press, NULL);
	mlx_hook(game->window.win, KeyRelease, KeyReleaseMask,
		handle_release, NULL);
	mlx_hook(game->window.win, DestroyNotify, StructureNotifyMask,
		close_game, NULL);
	mlx_hook(game->window.win, MotionNotify, PointerMotionMask,
		mouse_input, game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage: ./cub3d <SCENE_PATH>");
		return (EXIT_FAILURE);
	}
	g_game()->scene = parse_scene(av[1]);
	init_game();
	start_game();
	close_game(EXIT_SUCCESS, "");
	return (EXIT_SUCCESS);
}
