/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:00 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/04 10:21:42 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	char	*name;
	char	*ber;
	int		len;

	if (!path)
	{
		printf("File Name is Empry.\n");
		return (0);
	}
	len = ft_strlen(path);
	if (len <= 5)
	{
		printf("Invalid File Name.\n");
		return (0);
	}
	name = ft_substr(path, 0, len - 4);
	ber = ft_substr(path, len - 4, 4);
	return (check_extension_parts(name, ber));
}
