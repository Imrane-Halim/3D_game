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

void	start_game(void)
{
	// will be added later
	// mlx_mouse_hide(g_game()->window.mlx, g_game()->window.win);
	
	mlx_hook(g_game()->window.win, KeyPress, KeyPressMask, handle_press, NULL);
	mlx_hook(g_game()->window.win, KeyRelease, KeyReleaseMask,
		handle_release, NULL);
	mlx_hook(g_game()->window.win, DestroyNotify, StructureNotifyMask,
		close_game, NULL);
	
	// will be enabled before push
	// mlx_hook(g_game()->window.win, MotionNotify, PointerMotionMask,
	// 	mouse_input, NULL);

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
	//init_scene(av[1]);
	t_scene *scene = parse_map(av[1]);
	if (!scene)
	{
		printf("invalid scene\n");
		return (EXIT_FAILURE);
	}
	ft_memcpy(&g_game()->scene, scene, sizeof(t_scene));
	//g_game()->scene = *scene;
	g_game()->player.pos = (t_xy){100, 100};
	free(scene);
	init_game();
	start_game();
	return (EXIT_SUCCESS);
}
