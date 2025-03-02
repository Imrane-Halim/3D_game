/*
	coordinate system conventions used in this project:

				Y														 90°
				|														 |
				|												  		 |
		X ------+--------------> (X increases)			180° ------------+------------ 0°
				| (0, 0)												 |
				|														 |
				|														 |
				|														270°
				*
			(Y increases)

	other stuff:  (why 64, 32, 16? bitwise operations are faster than multiplication)
	-- the wall is going to be 64 units
	-- the player is goint to be 32 units
*/

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <mlx.h>
# include "common.h"

# define PI			3.141592653589793238462643383

// window dimentions
# define SPEED		16

// used in 2D map
# define TILESIZE	64

// screen res
# define WIDTH		1536
# define HEIGHT		832

// to switch between 2D and 3D view
# define DEBUG		1

// the size of the rectangle
# define RES		2

// the number of rays the palyer will case
# define NRAYS		WIDTH / RES

// maped keyboard keys
enum e_keys
{
	KEY_ESC = 65307,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100
};

//	*mlx and *win are used to control the X11 window
//	default res is going to be 1920x1080
typedef struct s_frame_data
{
	void	*img;
	void	*adr;
	int		bpp;
	int		line_lenght;
	int		endian;
}	t_frame_data;

typedef struct s_window
{
	void			*mlx;
	void			*win;
	t_frame_data	frame; // frame to display
}	t_window;

typedef struct s_player
{
	double	fov;	// field of view [1, 135]. default is 60
	unsigned int	height;	// default: 32

	// mose coordinates
	int		mouse_x;
	int		mouse_y;

	// position in the map/maze
	double	pos_x;
	double	pos_y;

	// point of viow (the direction the player is facing)
	double	dir_x;
	double	dir_y; // this will be use with the mouse later

	// other stuff like speed will be added later
}	t_player;


// The projection plane is a virtual 2D surface that represents what the player sees in the 3D world
// Video resolution is usually referred in pixels, so think of 1 pixel as equal to 1 unit.
// more information: https://permadi.com/1996/05/ray-casting-tutorial-5/
// default 1920x1080
typedef struct s_projection_plane
{
	unsigned short	width;
	unsigned short	height;
	double			angle_increment; // fov / plan.width
} t_projection_plane;

// a global struct that will contain all data about the game
typedef struct e_data
{
	t_player 			player;
	t_window 			window;
	t_projection_plane	plane;
	char				**map;
}	t_data;

/*
	what we can get so far:
		- distance from the player to the projection plane: 
			distance = plane.width / tan(fov / 2)
		- angle between rays
			e.x: plane.width = 320, fov = 60
			320 column (or units) = 60 degree
			so: 1 column = 60/320 degree
			angle between subsequent rays = 60/320 degree

	Checking intersections: 
	https://permadi.com/1996/05/ray-casting-tutorial-7/

*/

//	-- game struct initialaztion stuff
void	init_window(void);
void	init_plane(void);
void	init_player(void);
void	init_game_data(void);

//	-- free all memory and exit
int		clean_exit(int code);

//	-- the name said it all
void	move_player(float x, float y);

//	-- event handling stuff
int		keyboard_event_handler(int key, void *data);
int		Mouse_event_handler(void);

//	-- frame rendering stuff
void	put_pixel(int x, int y, int color);
void	draw_square(int x, int y, int width, int height, int color);
void	draw_background(void);
void	draw_player(void);
void	draw_map();
void	draw_mouse();
void 	draw_line(int x0, int y0, int x1, int y1);
int		draw_frame(void);

//	-- run game
void	start_game(void);


//  -- game logic
bool	has_obj_at(int x, int y, char obj);

#endif