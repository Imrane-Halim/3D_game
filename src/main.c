#include "parsing.h"
#include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("usage: ./cub <MAP_PATH>\n");
		return (EXIT_FAILURE);
	}
	printf("hello: %s\n", av[1]);
	return (EXIT_SUCCESS);
}