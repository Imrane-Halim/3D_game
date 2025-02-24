#include "parsing.h"
#include "cub3d.h"

char *map[] = {
	"111111",
	"100101",
	"101001",
	"1100N1",
	"111111"
};
// player possition: p[3][4];

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage: ./cub <MAP_PATH>\n");
		return (EXIT_FAILURE);
	}
	(void)av;
	void	*mlx, *win;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "hello from wsl");

	void *img;
	img = mlx_new_image(mlx, 10, 20);
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);

	return (EXIT_SUCCESS);
}