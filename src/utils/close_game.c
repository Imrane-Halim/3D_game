/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:13:44 by imrane            #+#    #+#             */
/*   Updated: 2025/05/05 09:50:32 by ihalim           ###   ########.fr       */
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
	free(g_game()->hand.path);
	free(g_game()->scene.textures.north.path);
	free(g_game()->scene.textures.south.path);
	free(g_game()->scene.textures.west.path);
	free(g_game()->scene.textures.east.path);
	free(g_game()->scene.textures.door.path);
}

int	close_game(int code, char *message)
{
	if (code && message)
		ft_putendl_fd(message, STDERR_FILENO);
	free_paths();
	free_map();
	destroy_images();
	mlx_destroy_image(g_game()->window.mlx, g_game()->window.frame.img);
	mlx_destroy_window(g_game()->window.mlx, g_game()->window.win);
	mlx_destroy_display(g_game()->window.mlx);
	free(g_game()->window.mlx);
	exit(code);
	return (code);
}
