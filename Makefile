NAME        = cub3D
LIBFT       = libft
INC         = include

# Base flags
CFLAGS      = -Wall -Wextra #-Werror
CFLAGS      += -I$(INC) -I$(LIBFT)
CFLAGS      += -g3 -Ofast

LDFLAGS     = -lmlx_Linux -lX11 -lXext -lm #-lz

# Source files
RAY_CAST    = $(wildcard src/ray_casting/*.c)
RENDERING   = $(wildcard src/rendering/*.c)
PARSING     = $(wildcard src/parsing/*.c)
UTILS       = $(wildcard src/utils/*.c)
GNL         = $(wildcard gnl/*.c)
MAIN        = src/main.c

SRC         = $(UTILS) $(RENDERING) $(PARSING) $(RAY_CAST) $(GNL) $(MAIN)
OBJ         = $(SRC:.c=.o)
RENDERING_OBJ = $(RENDERING:.c=.o)

# File to track current build mode
BUILD_MODE_FILE = .build_mode

# Default target (release mode)
all: release

release: | $(BUILD_MODE_FILE)
	@if [ "$$(cat $(BUILD_MODE_FILE))" != "release" ]; then \
		$(RM) $(RENDERING_OBJ); \
		echo "release" > $(BUILD_MODE_FILE); \
	fi
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS)"

debug: | $(BUILD_MODE_FILE)
	@if [ "$$(cat $(BUILD_MODE_FILE))" != "debug" ]; then \
		$(RM) $(RENDERING_OBJ); \
		echo "debug" > $(BUILD_MODE_FILE); \
	fi
	@$(MAKE) $(NAME) CFLAGS="$(CFLAGS) -D DEBUG"

$(NAME): $(OBJ)
	$(MAKE) bonus -C $(LIBFT) --silent
	$(CC) $(OBJ) $(LIBFT)/libft.a $(CFLAGS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_MODE_FILE):
	@mkdir -p $(dir $(BUILD_MODE_FILE))
	@echo "release" > $(BUILD_MODE_FILE)

clean:
	$(MAKE) clean -C $(LIBFT) --silent
	$(RM) $(OBJ) $(BUILD_MODE_FILE)

fclean: clean
	$(MAKE) fclean -C $(LIBFT) --silent
	$(RM) $(NAME)

re: fclean all

.PHONY: all release debug clean fclean re