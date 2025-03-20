#include "cub3d.h"

int Mouse_input(void)
{
    int x,y;

    mlx_mouse_get_pos(g_game.window.mlx, g_game.window.win, &x, &y);

    printf("x: %d, y: %d\n", x, y);

    return (0);
}
