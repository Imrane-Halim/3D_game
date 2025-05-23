/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:17:11 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 11:07:47 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(void)
{
	t_game	*game;

	game = g_game();
	game->window.mlx = mlx_init();
	game->window.win = mlx_new_window(game->window.mlx, WIDTH, HEIGHT, TITLE);
	game->window.frame.img = mlx_new_image(game->window.mlx, WIDTH, HEIGHT);
	game->window.frame.adr = mlx_get_data_addr(game->window.frame.img,
			&game->window.frame.bbp,
			&game->window.frame.line_length,
			&game->window.frame.endian);
}

void	init_minimap(void)
{
	t_xy	pos;

	pos.x = 9;
	pos.y = 550;
	g_game()->minimap.height = 200;
	g_game()->minimap.width = 200;
	g_game()->minimap.pos = pos;
	g_game()->minimap.floor_color = 0x000000;
	g_game()->minimap.wall_color = 0x0000ff;
	g_game()->minimap.player_color = 0xff0000;
	g_game()->minimap.door_color = 0xffff00;
}

t_image	load_img(char *path)
{
	t_image	img;

	img.img = mlx_xpm_file_to_image(g_game()->window.mlx, path, &img.width,
			&img.height);
	img.path = path;
	if (!img.img)
	{
		close_game(EXIT_FAILURE, TEX_LOAD_ERR);
	}
	img.adr = mlx_get_data_addr(img.img, &img.bbp, &img.line_length,
			&img.endian);
	return (img);
}

// todo: string literals to constants (macros)
void	init_textures(void)
{
	g_game()->scene.textures.north = load_img(
		g_game()->scene.textures.north.path);
	g_game()->scene.textures.south = load_img(
		g_game()->scene.textures.south.path);
	g_game()->scene.textures.east = load_img(
		g_game()->scene.textures.east.path);
	g_game()->scene.textures.west = load_img(
		g_game()->scene.textures.west.path);
	g_game()->scene.textures.door = load_img(
		ft_strdup("./textures/xpm/door.xpm"));
	g_game()->hand = load_img(ft_strdup("./textures/xpm/hand.xpm"));
}

void	init_player(t_xy pos, float angle)
{
	g_game()->player.fov = FOV * (PI / 180);
	g_game()->player.pos = pos;
	g_game()->player.angle = angle;
}
