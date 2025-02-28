#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include "libft.h"

char *map[] = {
	"111111",
	"1P0101",
	"101001",
	"110001",
	"111111"
};
// player possition: p[1][1];
int	clean_exit(int code);

#endif