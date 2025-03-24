#include "cub3d.h"

void	init_window()
{
	g_game.window.mlx = mlx_init();
	g_game.window.win = mlx_new_window(g_game.window.mlx, WIDTH, HEIGHT, TITLE);
	g_game.window.frame.img = mlx_new_image(g_game.window.mlx, WIDTH, HEIGHT);
	g_game.window.frame.adr = mlx_get_data_addr(g_game.window.frame.img, 
		&g_game.window.frame.bbp, &g_game.window.frame.line_length, &g_game.window.frame.endian);
}

void	init_player()
{
	// convert degree to radian
	g_game.player.fov = FOV * (PI / 180);

	// this will change after parsing is done
	// for example if stat is 64x64 add 1 to be 65x64
	g_game.player.pos.x = 64;
	g_game.player.pos.y = 64;
}

void	init_scene(char *path)
{
	(void)path;
	// todo:
	// g_game.scene = parse_map(path);
	static char *map[] = 
	{
		"111111111      111111111",
		"100000101      100000001",
		"100000001      100000001",
		"100010001111111100000001",
		"100001000000000100000001",
		"111100000000000100000001",
		"   100000000000D00000001",
		"111100000000000111111111",
		"10000000011110000000000111111",
		"10000000011110000000000000001",
		"10000000000000000000000000001",
		"11111111111111111111111111111",
		NULL
	};
	g_game.scene.map = ft_calloc(13, sizeof(char *));
	for (int i = 0; i < 12; i++)
	{
		g_game.scene.map[i] = ft_strdup(map[i]);
	}

	// note: width var holds the len of the logest line
	// height is obvious
	g_game.scene.m_width = 30;
	g_game.scene.m_height = 12;
	g_game.scene.floor_color = 0x292929;
	g_game.scene.ceiling_color = 0x4a4a4a;
}

void	init_minimap()
{
	g_game.map.height = 200;
	g_game.map.width = 200;
	g_game.map.pos = (t_xy){9, 550};
	g_game.map.floor_color = 0x000000;
	g_game.map.wall_color = 0x0000ff;
	g_game.map.player_color = 0xff0000;
	g_game.map.door_color = 0xffff00;
}

t_image	load_img(char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(g_game.window.mlx, path, &img.width, &img.height);
	img.adr = mlx_get_data_addr(img.img, &img.bbp, &img.line_length, &img.endian);
	return (img);
}

void	init_textures()
{
	g_game.scene.textures.north = load_img("textures/xpm/wall1.xpm");
	g_game.scene.textures.south = load_img("textures/xpm/wall2.xpm");
	g_game.scene.textures.east = load_img("textures/xpm/wall3.xpm");
	g_game.scene.textures.west = load_img("textures/xpm/wall4.xpm");
	g_game.scene.textures.door = load_img("textures/xpm/door.xpm");
	g_game.hand = load_img("textures/xpm/hand.xpm");
}

void	init_game()
{
	g_game.n_rays = WIDTH;
	init_window();
	init_player();
	init_textures();
	init_scene("todo");
	init_minimap();
}
