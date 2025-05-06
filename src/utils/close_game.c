/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:13:44 by imrane            #+#    #+#             */
/*   Updated: 2025/05/06 10:11:26 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(void)
{
	t_game	*game;

	game = g_game();
	if (game->scene.textures.north.img)
		mlx_destroy_image(game->window.mlx, game->scene.textures.north.img);
	if (game->scene.textures.south.img)
		mlx_destroy_image(game->window.mlx, game->scene.textures.south.img);
	if (game->scene.textures.east.img)
		mlx_destroy_image(game->window.mlx, game->scene.textures.east.img);
	if (game->scene.textures.west.img)
		mlx_destroy_image(game->window.mlx, game->scene.textures.west.img);
	if (game->scene.textures.door.img)
		mlx_destroy_image(game->window.mlx, game->scene.textures.door.img);
	if (game->hand.img)
		mlx_destroy_image(game->window.mlx, game->hand.img);
}

void	free_map(void)
{
	int	i;

	if (!g_game()->scene.map)
		return ;
	i = 0;
	while (g_game()->scene.map[i])
		free(g_game()->scene.map[i++]);
	free(g_game()->scene.map);
}
void	free_paths(void)
{
	t_textures *textures = &g_game()->scene.textures;

	free_textures(textures);
	//if (textures->north.path)
	//	free(textures->north.path);
	//if (textures->south.path)
	//	free(textures->south.path);
	//if (textures->west.path)
	//	free(textures->west.path);
	//if (textures->east.path)
	//	free(textures->east.path);
	//if (textures->door.path)
	//	free(textures->door.path);
}


int	close_game(int code, char *message)
{
	if (code && message)
		ft_putendl_fd(message, STDERR_FILENO);
	free_map();
	//free(g_game().scene);
	//free_scene(&(g_game()->scene));
	destroy_images();
	mlx_destroy_image(g_game()->window.mlx, g_game()->window.frame.img);
	mlx_destroy_window(g_game()->window.mlx, g_game()->window.win);
	mlx_destroy_display(g_game()->window.mlx);
	free(g_game()->window.mlx);
	//free_paths();
	exit(code);
	return (code);
}
