#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <math.h>
# include "mlx.h"
# include "common.h"

# define PI			3.14159265359
# define WIDTH		1526
# define HEIGHT		832
# define TILESIZE	64
# define TITLE		"Cub3D"

# define POS_STEP 16
# define AGL_STEP 0.1

/*
	possible implementation of s_scene;
		typedef struct s_scene
		{
			int	m_width;
			int	m_height;
			char **map;
		} t_scene;
*/

enum e_keys
{
	ESC_KEY = 65307,

	UP_KEY = 65362,
	DOWN_KEY = 65364,
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	
	W_KEY = 119,
	A_KEY = 97,
	S_KEY = 115,
	D_KEY = 100
};

typedef struct s_coordinates
{
	float	x;
	float	y;
}	t_coordinates;

typedef struct s_frame
{
	void	*img;
	void	*adr;
	int		bbp;
	int		line_length;
	int		endian;
}	t_frame;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_frame	frame;
}	t_window;

// fov: field of view
// angle: point of view
typedef struct s_player
{
	float			fov;
	t_coordinates	pos;
	t_coordinates	angle;
}	t_player;

typedef struct s_game
{
	t_player player;
	t_window window;
	t_scene scene;
}	t_game;

extern t_game	g_game;

/*
	frees all allocated memroy by mlx
	before exiting
	@param code: exit code
	@return always returns 0
*/
int		close_game(int code);


// initilazes the window struct
void	init_window();

// initializes the player struct
void	init_player();

// initializes the game struct
void	init_game();

/*
	handles keyboars KeyPress events
	@param keynum: the pressed key number
	@return always returns 0
*/
int		Keyboard_input(int keynum);

// todo
int		Mouse_input(void);

// inits all events stuff and starts game
void	start_game();

//------------------------------------------- player movements
void	ch_player_pos(int dir);
void	ch_player_xangle(float angle);


//------------------------------------------- rendring

// frame rendring function
int		render_frame();

/*
	@brief puts pixel in the frame.img
	@param x coordinate
	@param y coordinate
	@param color color
*/
void	put_pixel(t_coordinates coord, int color);



#endif