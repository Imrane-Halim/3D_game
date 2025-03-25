#include "cub3d.h"

void	destroy_images()
{
	if (g_game.scene.textures.north.img)
		mlx_destroy_image(g_game.window.mlx, g_game.scene.textures.north.img);
	if (g_game.scene.textures.south.img)
		mlx_destroy_image(g_game.window.mlx, g_game.scene.textures.south.img);
	if (g_game.scene.textures.east.img)
		mlx_destroy_image(g_game.window.mlx, g_game.scene.textures.east.img);
	if (g_game.scene.textures.west.img)
		mlx_destroy_image(g_game.window.mlx, g_game.scene.textures.west.img);
	if (g_game.scene.textures.door.img)	
		mlx_destroy_image(g_game.window.mlx, g_game.scene.textures.door.img);
	if (g_game.hand.img)
		mlx_destroy_image(g_game.window.mlx, g_game.hand.img);
}

void	free_map()
{
	int	i;

	i = 0;
	while (g_game.scene.map[i])
		free(g_game.scene.map[i++]);
	free(g_game.scene.map);
}

int		close_game(int code, char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	free_map();
	destroy_images();
	mlx_destroy_image(g_game.window.mlx, g_game.window.frame.img);
	mlx_destroy_window(g_game.window.mlx, g_game.window.win);
	mlx_destroy_display(g_game.window.mlx);
	free(g_game.window.mlx);
	exit(code);
	return (code);
}