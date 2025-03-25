/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:17:11 by imrane            #+#    #+#             */
/*   Updated: 2025/03/25 19:17:12 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(void)
{
	g_game.window.mlx = mlx_init();
	g_game.window.win = mlx_new_window(g_game.window.mlx, WIDTH, HEIGHT, TITLE);
	g_game.window.frame.img = mlx_new_image(g_game.window.mlx, WIDTH, HEIGHT);
	g_game.window.frame.adr = mlx_get_data_addr(g_game.window.frame.img,
			&g_game.window.frame.bbp, &g_game.window.frame.line_length,
			&g_game.window.frame.endian);
}

void	init_minimap(void)
{
	g_game.minimap.height = 200;
	g_game.minimap.width = 200;
	g_game.minimap.pos = (t_xy){9, 550};
	g_game.minimap.floor_color = 0x000000;
	g_game.minimap.wall_color = 0x0000ff;
	g_game.minimap.player_color = 0xff0000;
	g_game.minimap.door_color = 0xffff00;
}

t_image	load_img(char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(g_game.window.mlx, path, &img.width,
			&img.height);
	if (!img.img)
		close_game(EXIT_FAILURE, TEX_LOAD_ERR);
	img.adr = mlx_get_data_addr(img.img, &img.bbp, &img.line_length,
			&img.endian);
	return (img);
}

// todo: string literals to constants (macros)
void	init_textures(void)
{
	g_game.scene.textures.north = load_img("textures/xpm/wall1.xpm");
	g_game.scene.textures.south = load_img("textures/xpm/wall2.xpm");
	g_game.scene.textures.east = load_img("textures/xpm/wall3.xpm");
	g_game.scene.textures.west = load_img("textures/xpm/wall4.xpm");
	g_game.scene.textures.door = load_img("textures/xpm/door.xpm");
	g_game.hand = load_img("textures/xpm/hand.xpm");
}

void	init_game(void)
{
	g_game.n_rays = WIDTH;
	init_window();
	init_textures();
	init_minimap();
}
