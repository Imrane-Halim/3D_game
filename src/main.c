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
	data.player.angle_x = 0;
	data.player.angle_y = 0;
	data.player.fov = 60 * (PI / 180);
	data.player.height = 32;
	data.player.pos_x = 64;
	data.player.pos_y = 64;
	data.player.mouse_x = 0;
	data.player.mouse_y = 0;
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
		if (new_y < 0 || new_y + 8 >= HEIGHT)
			return ;
		if (new_x < 0 || new_x + 8 >= WIDTH)
			return ;
		if (has_obj_at(new_x, new_y + 8, '1'))
			return ;
		if (has_obj_at(new_x + 8, new_y, '1'))
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
	data.player.mouse_x = x;
	data.player.mouse_y = y;
	// mlx_pixel_put(data.window.mlx, data.window.win, x, y, 255);
	// printf("x: %d, y: %d\n", x, y);
	return (0);
}

// ------------------- frame rendring stuff
void	put_pixel(int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
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
	draw_square(data.player.pos_x, data.player.pos_y, 16, 16, 0xffb700);
}

void	draw_map()
{
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			if (map[y][x] == '1')
				draw_square(x * TILESIZE, y * TILESIZE,
				TILESIZE - 1, TILESIZE - 1, 0x403f3e);
			if (map[y][x] == '0')
				draw_square(x * TILESIZE, y * TILESIZE,
				TILESIZE - 1, TILESIZE - 1, 0xffffff);
		}
	}
}

void	draw_mouse()
{
	int	x;
	int	y;

	x = data.player.mouse_x - 4;
	y = data.player.mouse_y - 4;
	if (x < 0 || y < 0 || y >= HEIGHT || x >= WIDTH)
		draw_square(x + 4, y + 4, 8, 8, 0xff0000);
	else
		draw_square(x, y, 8, 8, 0xff0000);
}

// this functin draws a line between the player 
// positin and the mouse position
void draw_line(int x0, int y0, int x1, int y1)
{
    int dx, dy, p;
    int stepx, stepy;
    
    dx = abs(x1 - x0);
    dy = abs(y1 - y0);
    stepx = (x0 < x1) ? 1 : -1;
    stepy = (y0 < y1) ? 1 : -1;
    int steep = 0;
    if (dy > dx) {
        int temp = dx;
        dx = dy;
        dy = temp;
        steep = 1;
    }
    p = 2 * dy - dx;
    for (int i = 0; i <= dx; i++)
    {
        put_pixel(x0, y0, 0xff0000);
        if (p >= 0)
        {
            if (steep) x0 += stepx;
            else y0 += stepy;
            p = p - 2 * dx;
        }
        if (steep) y0 += stepy;
        else x0 += stepx;
        p = p + 2 * dy;
    }
}

int	draw_frame(void)
{
	draw_background();
	draw_map();
	draw_player();
	draw_mouse();
	draw_line(data.player.pos_x + 8, data.player.pos_y + 8,
		data.player.mouse_x, data.player.mouse_y);
	mlx_put_image_to_window(data.window.mlx, data.window.win,
		data.window.frame.img, 0, 0);
	return (0);
}

// -------------- some game logic stuff
// this function takes the pixel coordinates
bool	has_obj_at(int x, int y, char obj)
{
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return (false);
	return (map[y / TILESIZE][x / TILESIZE] == obj);
}

// -------------- run game --
void	start_game(void)
{
	mlx_hook(data.window.win, KeyPress, KeyPressMask, keyboard_event_handler, NULL);
	mlx_hook(data.window.win, DestroyNotify, StructureNotifyMask, clean_exit, NULL);
	mlx_hook(data.window.win, MotionNotify, PointerMotionMask, Mouse_event_handler, NULL);
	mlx_mouse_hide(data.window.mlx, data.window.win);
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