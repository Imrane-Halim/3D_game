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

# define FOV		60
# define POS_STEP 	8
# define AGL_STEP	0.08
# define FORWARD	1
# define BACKWARD  -1
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

typedef struct s_xy
{
	float	x;
	float	y;
}	t_xy;

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

typedef struct s_pressed_key
{
	bool	left;
	bool	right;
	bool	up;
	bool	down;

	bool	w;
	bool	s;
	bool	a;
	bool	d;
}	t_pressed_key;

// fov: field of view
// angle: point of view
typedef struct s_player
{
	float			fov;
	t_xy			pos;
	float			angle;
}	t_player;

typedef struct s_game
{
	t_player		player;
	t_window		window;
	t_scene			scene;
	t_pressed_key	key;
	int				n_rays;
	int				timer;
}	t_game;

extern t_game	g_game;

//---------------- memory managment

int		close_game(int code);

//---------------- initialazation

void	init_window();
void	init_player();
void	init_game();

//---------------- events handling stuff

int 	handle_release(int keynum);
int 	handle_press(int keynum);
int		handle_key(int keynum, bool is_pressed);

int		Keyboard_input();
int		Mouse_input(void); // todo

//---------------- player movements

// void	ch_player_pos(int dir);
// void	ch_player_xangle(float angle);

//---------------- this where everything stars

void	start_game();

//---------------- ray casting logic
t_xy	cast_ray(float angle);

//---------------- rendring

void	put_pixel(t_xy coord, int color);
void	draw_square(t_xy coord, int height, int width, int color);
void	draw_line(t_xy start, t_xy end, int color);

void	draw_2D_view(void);
void	draw_3D_view(void);

int		render_frame();

#endif