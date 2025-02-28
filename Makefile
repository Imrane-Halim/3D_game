NAME 		= cub3d
LIBFT		= libft
INC			= include

CFLAGS 		= -Wall -Wextra -Werror -g3 #-fsanitize=address
CFLAGS		+= -I$(INC) -I$(LIBFT)
CFLAGS		+= -lmlx_Linux -lX11 -lXext #-lm -lz
CFLAGS		+= -O3 # no optimazation to make debuging easier, change it to -03 before push

RENDERING	= $(wildcard src/rendering/*.c)
PARSING 	= $(wildcard src/parsing/*.c)
UTILS 		= $(wildcard src/utils/*.c)

MAIN		= src/main.c

SRC = 	$(RENDERING) $(PARSING) $(MAIN)

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) bonus -C $(LIBFT) --silent
	$(CC) $(OBJ) $(LIBFT)/libft.a $(CFLAGS) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT) --silent
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT) --silent
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)