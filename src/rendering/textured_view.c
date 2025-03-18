#include "cub3d.h"

static void	draw_floor_ceiling()
{
	draw_square((t_xy){0, 0}, HEIGHT / 2, WIDTH, g_game.scene.ceiling_color);
	draw_square((t_xy){0, HEIGHT / 2}, HEIGHT / 2, WIDTH, g_game.scene.floor_color);
}

// this will be added later
static inline int		shade_color(int color, float dist)
{
	float	factor = 1.0 - fmin(dist / (TILESIZE * 10.0), 0.8);
	int r = ((color >> 16) & 0xff) * factor;
	int g = ((color >> 8) & 0xff) * factor;
	int b = ((color) & 0xff) * factor;
	return (r << 16 | g << 8 | b);
}

static inline int	get_pixel_color(t_image tex, t_xy pos)
{
	char	*src;
	int		x;
	int		y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (x < 0 || y < 0 || x >= tex.width || y >= tex.height)
		return (0);
	src = tex.adr + (y * tex.line_length + x * (tex.bbp / 8));
	return (*(unsigned int *)src);
}

/*
static inline void draw_tex_slice(float dist, t_image tex, int bottom, int top, int x, t_ray ray)
{
    int color;
    
    // Calculate the exact hit position on the wall for x-coordinate in texture
    float wall_x;
    if (ray.dir == NORTH || ray.dir == SOUTH)
        wall_x = ray.hit.x - floor(ray.hit.x / TILESIZE) * TILESIZE;
    else
        wall_x = ray.hit.y - floor(ray.hit.y / TILESIZE) * TILESIZE;
    
    // Convert to texture coordinate
    int tex_x = (int)(wall_x * tex.width / TILESIZE);
    
    // Fix texture orientation for certain directions
    if ((ray.dir == WEST) || (ray.dir == NORTH))
        tex_x = tex.width - tex_x - 1;
    
    // Calculate the height of this wall slice
    int wall_height = bottom - top;
    
    // Calculate where the wall would theoretically start if not clipped
    float theoretical_height = (TILESIZE / dist) * ((WIDTH / 2) / tan(FOV * PI / 360));
    float theoretical_top = (HEIGHT - theoretical_height) / 2;
    
    // For vertical texture mapping
    for (int y = top; y < bottom; y++)
    {
        // Map screen y-coordinate to texture y-coordinate
        // This accounts for walls taller than the screen
        float y_ratio = (y - top) / (float)wall_height;
        
        // Adjust for clipping at top of screen
        if (top == 0 && theoretical_top < 0) {
            y_ratio = (y + fabs(theoretical_top)) / theoretical_height;
        }
        
        int tex_y = (int)(y_ratio * tex.height);
        
        // Get the texture color
        color = get_pixel_color(tex, (t_xy){tex_x, tex_y});
        
        // Apply distance shading
        color = shade_color(color, dist);
        
        // Draw the pixel
        put_pixel((t_xy){x, y}, color);
    }
}
*/

static inline void	draw_tex_slice(float dist, t_image tex, int bottom, int top, int x)
{
	int color;
	int	tex_x;
	for (int y = top; y < bottom; y++)
	{	
		tex_x = x % TILESIZE;
		color = get_pixel_color(tex, (t_xy){tex_x, y % TILESIZE});
		color = shade_color(color, dist);
		put_pixel((t_xy){x, y}, color);
	}
}

static void	draw_slice(t_ray ray, float ray_angle, int ray_num)
{
	float	dist = distance(g_game.player.pos, ray.hit) * cos(ray_angle - g_game.player.angle);
	float	wall_height = (TILESIZE / dist) * ((WIDTH / 2) / tan(FOV * PI / 360));
	int		wall_top = (HEIGHT - wall_height) / 2;
	int		wall_bottom = wall_top + wall_height;

	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= HEIGHT)
		wall_bottom = HEIGHT - 1;

	t_image tex = g_game.scene.textures.west;
	if (ray.dir == NORTH)
		tex = g_game.scene.textures.north;
	else if (ray.dir == SOUTH)
		tex = g_game.scene.textures.south;
	else if (ray.dir == EAST)
		tex = g_game.scene.textures.east;
		
	draw_tex_slice(dist, tex, wall_bottom, wall_top, ray_num);
}

inline void	draw_textured()
{
	draw_floor_ceiling();

	t_ray	ray;
	float	ray_angle;

	float	s_angle;
	float	angle_step;

	int		i;

	i = 0;
	s_angle = g_game.player.angle - (FOV * PI / 180) / 2;
	angle_step = (FOV * PI / 180) / g_game.n_rays;
	while (i < g_game.n_rays)
	{
		ray_angle = s_angle + i * angle_step;
		ray = cast_ray(ray_angle);
		draw_slice(ray, ray_angle, i);
		i++;
	}
}
