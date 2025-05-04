/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:57:17 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/04 10:26:09 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool check(char *str, char *prefix)
{
	while (*prefix && *str)
	{
		if (*str != *prefix)
			return (false);
		str++;
		prefix++;
	}
	return (*str == ' ');
}
bool check_prefix(char **paths)
{
	if (!check(paths[0], "NO"))
	{
		printf("Error: Prefix must be 'NO'\n");
		return (false);
	}
	if (!check(paths[1], "SO"))
	{
		printf("Error: Prefix must be 'SO'\n");
		return (false);
	}
	if (!check(paths[2], "WE"))
	{
		printf("Error: Prefix must be 'WE'\n");
		return (false);
	}
	if (!check(paths[3], "EA"))
	{
		printf("Error: Prefix must be 'EA'\n");
		return (false);
	}
	return (true);
}

bool extract_paths_2(char **paths)
{
	char *tmp;
	char *new_path;
	int i;

	i = 0;
	while (i < 4)
	{
		tmp = ft_strchr(paths[i], ' ');
		if (!tmp)
			return (false);
		while (*tmp && *tmp == ' ')
			tmp++;
		if (!tmp)
			return (false);
		new_path = ft_strdup(tmp);
		if (!new_path)
			return (false);
		free(paths[i]);
		paths[i] = new_path;
		i++;
	}
	return (true);
}
