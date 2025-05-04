NAME 		= cub3d
LIBFT		= libft
INC			= include

CFLAGS 		= -Wall -Wextra -Werror
CFLAGS		+= -I$(INC) -I$(LIBFT)
CFLAGS		+= -g3 #-fsanitize=address
CFLAGS		+= -Ofast # optimazation

LDFLAGS		= -lmlx_Linux -lX11 -lXext -lm #-lz

RAY_CAST	= $(wildcard src/ray_casting/*.c)
RENDERING	= $(wildcard src/rendering/*.c)
PARSING 	= $(wildcard src/parsing/*.c)
UTILS 		= $(wildcard src/utils/*.c)

MAIN		= src/main.c

SRC = 	$(UTILS) $(RENDERING) $(PARSING) $(RAY_CAST) $(MAIN)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(SRC)
	$(MAKE) bonus -C $(LIBFT) --silent
	$(CC) $(OBJ) $(LIBFT)/libft.a $(CFLAGS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT) --silent
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT) --silent
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
