NAME 		= cub
CFLAGS 		= -Wall -Wextra -Werror -g3 #-fsanitize=address
LIBFT		= libft
INC			= include
CFLAGS		+= -I$(INC) -I$(LIBFT)

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