#include "cub3d.h"

t_game	g_game;

void	start_game()
{
	mlx_hook(g_game.window.win, KeyPress, KeyPressMask, Keyboard_input, NULL);
	mlx_hook(g_game.window.win, DestroyNotify, StructureNotifyMask, close_game, NULL);
	mlx_loop_hook(g_game.window.mlx, render_frame, NULL);
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