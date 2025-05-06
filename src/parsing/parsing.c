/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:42 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/06 09:42:56 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void exit_with_failure()
{
	printf("Error.\n");
		//free_scene(scene);
	exit(EXIT_FAILURE);
}

t_scene	parse_map(char *path)
{
	t_scene	*scene;
	char	*content;

	if (!path)
		exit_with_failure();
	if (!check_extension(path))
	{
		printf("Invalid extention.\n");
		exit_with_failure();
	}
	content = file_to_string(path);
	if (!content)
		exit_with_failure();
	scene = init_scene(content);
	free(content);
	if (!scene)
		exit_with_failure();
	return (*scene);
}
