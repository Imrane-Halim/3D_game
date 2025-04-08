#include "cub3d.h"

void	init_scene(char *path)
{
	t_game		*game;
	static char	*map[] = {
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
			NULL};

	(void)path;
	// todo:
	// g_game()->scene = parse_map(path);
	game = g_game();
	game->scene.map = ft_calloc(13, sizeof(char *));
	for (int i = 0; i < 12; i++)
	{
		game->scene.map[i] = ft_strdup(map[i]);
	}
	// note: width var holds the len of the logest line
	// height is obvious
	game->scene.m_width = 30;
	game->scene.m_height = 12;
	game->scene.floor_color = 0x292929;
	game->scene.ceiling_color = 0x4a4a4a;

	game->scene.textures.north.path = "textures/xpm/wall1.xpm";
	game->scene.textures.south.path = "textures/xpm/wall2.xpm";
	game->scene.textures.east.path = "textures/xpm/wall3.xpm";
	game->scene.textures.west.path = "textures/xpm/wall4.xpm";
	game->scene.textures.door.path = "textures/xpm/door.xpm";
	game->hand.path = "textures/xpm/hand.xpm";
}
