/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:00 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/03 12:43:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_folder(char *folder)
{
	if (!folder)
		return (0);
	if (ft_strncmp(folder, "maps/", 5) != 0)
	{
		free(folder);
		return (0);
	}
	free(folder);
	return (1);
}

int	check_extension_parts(char *name, char *ber)
{
	int	valid;

	if (!name || !ber)
	{
		free(name);
		free(ber);
		return (0);
	}
	valid = (name && ber && ft_strncmp(ber, ".cub", 4) == 0);
	free(name);
	free(ber);
	return (valid);
}

int	check_extension(char *path)
{
	char	*folder;
	char	*name;
	char	*ber;
	int		len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (!path || len <= 9)
		return (0);
	folder = ft_substr(path, 0, 5);
	if (!check_folder(folder))
		return (0);
	name = ft_substr(path, 5, len - 9);
	ber = ft_substr(path, len - 4, 4);
	return (check_extension_parts(name, ber));
}
