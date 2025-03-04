#include "cub3d.h"

int		close_game(int code)
{
	// free_map();
	// free_images();
	mlx_destroy_image(g_game.window.mlx, g_game.window.frame.img);
	mlx_destroy_window(g_game.window.mlx, g_game.window.win);
	mlx_destroy_display(g_game.window.mlx);
	free(g_game.window.mlx);
	exit(code);
}
