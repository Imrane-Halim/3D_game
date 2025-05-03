/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:21:16 by imrane            #+#    #+#             */
/*   Updated: 2025/05/03 12:42:19 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "common.h"
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
 # include <mlx.h>

# define PI 3.14159265359
# define WIDTH 1366
# define HEIGHT 768
# define TILESIZE 64
# define TITLE "Cub3D"

# define FOV 60
# define POS_STEP 4
# define AGL_STEP 0.02
# define FORWARD 1
# define BACKWARD -1
# define MOUSE_SENS 0.001f

// error messages
# define TEX_LOAD_ERR "Error\nFailed to load texture"

typedef enum e_keys
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
}					t_keys;

typedef struct s_xy
{
	float			x;
	float			y;
}					t_xy;

typedef struct s_window
{
	void			*mlx;
	void			*win;
	t_image			frame;
}					t_window;

typedef struct s_pressed_key
{
	bool			left;
	bool			right;
	bool			up;
	bool			down;

	bool			w;
	bool			s;
	bool			a;
	bool			d;
}					t_pressed_key;

// fov: field of view
// angle: point of view
typedef struct s_player
{
	float			fov;
	t_xy			pos;
	float			angle;
}					t_player;

typedef struct s_minimap
{
	t_xy			pos;
	int				width;
	int				height;

	int				floor_color;
	int				wall_color;
	int				door_color;

	int				player_color;
}					t_minimap;

typedef struct s_game
{
	t_player		player;
	t_window		window;
	t_scene			scene;
	t_pressed_key	key;
	t_minimap		minimap;
	t_image			hand;
	int				n_rays;
	int				timer;
}					t_game;

//---------------------------
typedef enum e_dirs
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR
}					t_dirs;

typedef struct s_ray
{
	t_xy			hit;
	t_dirs			dir;
}					t_ray;

typedef struct s_casted_ray
{
	t_image			tex;
	t_ray			ray;
	float			dist;
	float			slice_hieght;
	int				ray_num;
	int				wall_top;
	int				wall_bottom;
}					t_casted_ray;

//===============parising======================

//===============================================

//---------------------------

t_game				*g_game(void);

//---------------- memory managment

int					close_game(int code, char *message);

//---------------- initialazation

void				init_window(void);
void				init_player(t_xy start_pos, float start_angle);
void				init_game(void);
void				init_minimap(void);
void				init_textures(void);

//---------------- events handling stuff

int					handle_release(int keynum);
int					handle_press(int keynum);
int					handle_key(int keynum, bool is_pressed);

int					keyboard_input(void);
int					mouse_input(int x, int y, void *data);

//---------------- player movements

void				ch_player_xangle(float angle);
void				ch_player_pos(int dir, bool is_strafe);

//---------------- here where everything stars

void				start_game(void);

//---------------- ray casting logic
t_ray				cast_ray(float angle);

//---------------- math
char				obj_hit(t_xy cord);
float				distance(t_xy a, t_xy b);

//---------------- rendring

void				put_pixel(t_xy coord, int color);
int					get_pixel_color(t_image tex, t_xy pos);
void				draw_square(t_xy coord, int height, int width, int color);
void				draw_line(t_xy start, t_xy end, int color);

// these 2 are for debuging or learining
// purposes only, no textures, nothing :)
//void				draw_2D_view(void);
//void				draw_3D_view(void);

void				draw_textured(void);

void				draw_minimap(void);

int					render_frame(void);

#endif