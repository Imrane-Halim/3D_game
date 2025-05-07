/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:11:00 by ihalim            #+#    #+#             */
/*   Updated: 2025/05/07 10:17:47 by ihalim           ###   ########.fr       */
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

int	game_loop(void)
{
	g_game()->timer++;
	keyboard_input();
	render_frame();
	return (0);
}

// mlx_hide_mouse()
void	start_game(void)
{
	mlx_hook(g_game()->window.win, KeyPress, KeyPressMask, handle_press, NULL);
	mlx_hook(g_game()->window.win, KeyRelease, KeyReleaseMask,
		handle_release, NULL);
	mlx_hook(g_game()->window.win, DestroyNotify, StructureNotifyMask,
		close_game, NULL);
	mlx_hook(g_game()->window.win, MotionNotify, PointerMotionMask,
		mouse_input, NULL);
	mlx_loop_hook(g_game()->window.mlx, game_loop, NULL);
	mlx_loop(g_game()->window.mlx);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage: ./cub3d <SCENE_PATH>");
		return (EXIT_FAILURE);
	}
	g_game()->scene = parse_map(av[1]);
	/*
		todo: player position
		void	init_player(pos, angle);

		ANGLE:	N S E W (PI / 2, PI + PI / 2, 0, PI)
		POS:	pos better be pos + {32, 32};
	*/
	init_game();
	start_game();
	return (EXIT_SUCCESS);
}
