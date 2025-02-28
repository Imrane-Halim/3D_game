#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include "libft.h"

char *map[] = {
	"111111111111111111111111",
	"1P0100000000000000000001",
	"101000001110110000000001",
	"100000000000000000001001",
	"111111111111111111111111"
};
// player possition: p[1][1];
int	clean_exit(int code);

#endif