#include "parsing.h"
#include "cub3d.h"

t_data data;

// ----------------------- initializing data
void	init_window()
{
	data.window.mlx = mlx_init();
	if (!data.window.mlx)
	{
		printf("mlx_init: failed!");
		exit(EXIT_FAILURE);
	}
	data.window.win = mlx_new_window(data.window.mlx, WIDTH, HEIGHT, "cub3d");
	if (!data.window.win)
	{
		mlx_destroy_display(data.window.mlx);
		free(data.window.mlx);
		printf("mlx_new_window: failed!");
		exit(EXIT_FAILURE);
	}
	data.window.frame = mlx_new_image(data.window.mlx, WIDTH, HEIGHT);
	if (!data.window.frame)
	{
		mlx_destroy_window(data.window.mlx, data.window.win);
		mlx_destroy_display(data.window.mlx);
		free(data.window.mlx);
		printf("mlx_new_image: failed!");
		exit(EXIT_FAILURE);
	}
}

void	init_plane()
{
	data.plane.width = WIDTH;
	data.plane.height = HEIGHT;
	data.plane.angle_increment = (double)WIDTH / (double)data.player.fov;
}

void	init_player()
{
	// this will chage when parsing part is done;
	data.player.dir_x = 0;
	data.player.dir_y = 0;
	data.player.fov = 60;
	data.player.height = 32;
	data.player.pos_x = 1;
	data.player.pos_y = 1;
}

void	init_game_data()
{
	init_window();
	init_player();
	init_plane();

	data.map = map;	// todo: use parsed map insted
}

// ------------------ free memory before exit
int		clean_exit()
{
	// free_images(); // todo
	mlx_destroy_image(data.window.mlx, data.window.frame);
	mlx_destroy_window(data.window.mlx, data.window.win);
	mlx_destroy_display(data.window.mlx);
	free(data.window.mlx);
	// free_map(); todo
	exit(EXIT_SUCCESS);
	return (0);
}

// --------------------- events handling stuff
int		keyboard_event_handler(int key, void *data)
{
	(void)data;
	// printf("key: %d\n", key);
	if (key == KEY_ESC)
		clean_exit();
	return (0);
}

int		Mouse_event_handler()
{
	int x, y;
	mlx_mouse_get_pos(data.window.mlx, data.window.win, &x, &y);
	//mlx_pixel_put(data.window.mlx, data.window.win, x, y, 255);
	// printf("x: %d, y: %d\n", x, y);
	return (0);
}

void	start_game()
{
	mlx_hook(data.window.win, KeyPress, KeyPressMask, keyboard_event_handler, NULL);
	mlx_hook(data.window.win, DestroyNotify, StructureNotifyMask, clean_exit, NULL);
	// mlx_hook(data.window.win, MotionNotify, PointerMotionMask, Mouse_event_handler, NULL);
	mlx_loop(data.window.mlx);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		printf("usage: ./cub <MAP_PATH>\n");
		return (EXIT_FAILURE);
	}

	init_game_data();
	// parse_map(); // todo
	start_game();
	return (EXIT_SUCCESS);
}