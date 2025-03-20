#include "cub3d.h"

t_game	g_game;

int		game_loop()
{
	g_game.timer++;
	Keyboard_input();
	render_frame();
	return (0);
}

void	start_game()
{
	// will be added later 
	//mlx_mouse_hide(g_game.window.mlx, g_game.window.win);

	mlx_hook(g_game.window.win, KeyPress, KeyPressMask, handle_press, NULL);
	mlx_hook(g_game.window.win, KeyRelease, KeyReleaseMask, handle_release, NULL);
	mlx_hook(g_game.window.win, DestroyNotify, StructureNotifyMask, close_game, NULL);
	
	mlx_hook(g_game.window.win, MotionNotify, PointerMotionMask, Mouse_input, NULL);

	mlx_loop_hook(g_game.window.mlx, game_loop, NULL);
	mlx_loop(g_game.window.mlx);
}

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		printf("usage: ./cub3d <SCENE_PATH>");
		return (EXIT_FAILURE);
	}
	init_game();
	start_game();
	return (EXIT_SUCCESS);
}