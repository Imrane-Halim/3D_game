#include "cub3d.h"
#include "parsing.h"

t_data	data;

// ----------------------- initializing data
void	init_window(void)
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
		clean_exit(1);
		printf("mlx_new_window: failed!");
		exit(EXIT_FAILURE);
	}
	data.window.frame.img = mlx_new_image(data.window.mlx, WIDTH, HEIGHT);
	if (!data.window.frame.img)
	{
		clean_exit(1);
		printf("mlx_new_image: failed!");
		exit(EXIT_FAILURE);
	}
	data.window.frame.adr = mlx_get_data_addr(data.window.frame.img,
			&data.window.frame.bpp, &data.window.frame.line_lenght,
			&data.window.frame.endian);
}

void	init_plane(void)
{
	data.plane.width = WIDTH;
	data.plane.height = HEIGHT;
	data.plane.angle_increment = (double)WIDTH / (double)data.player.fov;
}

void	init_player(void)
{
	// this will chage when parsing part is done;
	data.player.dir_x = 0;
	data.player.dir_y = 0;
	data.player.fov = 60;
	data.player.height = 32;
	data.player.pos_x = 64;
	data.player.pos_y = 64;
}

void	init_game_data(void)
{
	init_window();
	init_player();
	init_plane();
	data.map = map; // todo: use parsed map insted
}

// ------------------ free memory before exit
int	clean_exit(int code)
{
	// free_images(); // todo
	mlx_destroy_image(data.window.mlx, data.window.frame.img);
	mlx_destroy_window(data.window.mlx, data.window.win);
	mlx_destroy_display(data.window.mlx);
	free(data.window.mlx);
	// free_map(); todo
	exit(code);
	return (0);
}

// --------------------- movement stuff
void	move_player(float x, float y)
{
	float	new_x;
	float	new_y;

	new_x = data.player.pos_x + x;
	new_y = data.player.pos_y + y;
	
	// if (new_x < 0 || new_x >= WIDTH)
	// 	return ;
	// if (new_y < 0 || new_y >= HEIGHT)
	// 	return ;
	if (DEBUG)
	{
		if (new_y < 0 || new_y + 16 >= HEIGHT)
			return ;
		if (new_x < 0 || new_x + 16 >= WIDTH)
			return ;
	}
	
	data.player.pos_x += x;
	data.player.pos_y += y;

	// printf("x: %d, y: %d\n", new_x, new_y);
}

// --------------------- events handling stuff
int	keyboard_event_handler(int key, void *data)
{
	(void)data;
	// printf("key: %d\n", key);
	if (key == KEY_ESC)
		clean_exit(0);
	else if (key == KEY_UP)
		move_player(0, -SPEED);
	else if (key == KEY_DOWN)
		move_player(0, SPEED);
	else if (key == KEY_LEFT)
		move_player(-SPEED, 0);
	else if (key == KEY_RIGHT)
		move_player(SPEED, 0);
	return (0);
}

// this function will be used later to
// chnage the pov using mouse movments
int	Mouse_event_handler(void)
{
	int x, y;
	mlx_mouse_get_pos(data.window.mlx, data.window.win, &x, &y);
	// mlx_pixel_put(data.window.mlx, data.window.win, x, y, 255);
	// printf("x: %d, y: %d\n", x, y);
	return (0);
}

// ------------------- frame rendring stuff
void	put_pixel(int x, int y, int color)
{
	char	*dst;

	dst = data.window.frame.adr + (y * data.window.frame.line_lenght + x
			* (data.window.frame.bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(int x, int y, int width, int height, int color)
{
	int	i;
	int	j;

	i = y;
	while (i < height + y)
	{
		j = x;
		while (j < width + x)
		{
			put_pixel(j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_background(void)
{
	draw_square(0, 0, WIDTH, HEIGHT, 0x403f3e);
}

void	draw_player(void)
{
	draw_square(data.player.pos_x, data.player.pos_y, 32, 32, 0xffb700);
}

void	draw_map()
{
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, 64, 0xffffff);
		}
	}
}

int	draw_frame(void)
{
	draw_background();
	draw_map();
	draw_player();
	mlx_put_image_to_window(data.window.mlx, data.window.win,
		data.window.frame.img, 0, 0);
	return (0);
}

void	start_game(void)
{
	mlx_hook(data.window.win, KeyPress, KeyPressMask, keyboard_event_handler, NULL);
	mlx_hook(data.window.win, DestroyNotify, StructureNotifyMask, clean_exit, NULL);
	// mlx_hook(data.window.win, MotionNotify, PointerMotionMask,
	// Mouse_event_handler, NULL);
	mlx_loop_hook(data.window.mlx, draw_frame, NULL);
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