#include "cub3d.h"

void	draw_floor_ceiling()
{
	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, g_game.scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2, WIDTH, g_game.scene.floor_color);
}

inline void	draw_3D_view(void)
{
	draw_floor_ceiling();
	
}