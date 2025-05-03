/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:42 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/03 12:43:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_scene	*parse_map(char *path)
{
	t_scene	*scene;
	char	*content;

	if (!path)
		return (NULL);
	if (!check_extension(path))
	{
		printf("Invalid extention.\n");
		return (NULL);
	}
	content = file_to_string(path);
	if (!content)
		return (NULL);
	scene = init_scene(content);
	free(content);
	return (scene);
}
