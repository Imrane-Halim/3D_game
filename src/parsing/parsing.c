/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:42 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/06 15:51:44 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void exit_with_failure(char *message)
{
	printf("%s\n",message);
	exit(EXIT_FAILURE);
}
t_scene	parse_map(char *path)
{
	t_scene	*scene;
	char	*content;

	if (!path)
		exit_with_failure("Error: Path is null.\n");
	if (!check_extension(path))
		exit_with_failure("Error: Invalid extension.\n");
	content = file_to_string(path);
	if (!content)
		exit_with_failure("Error: Cannot read content of map.\n");
	scene = init_scene(content);
	free(content);
	if (!scene)
		exit_with_failure("Error: Failed to initialize scene.\n");
	return (*scene);
}
