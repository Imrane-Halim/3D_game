/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:05:51 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/03 12:43:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	count_dimensions(char **string, int *height, int *width, int *min)
{
	int	i;
	int	size;

	i = 0;
	*height = 0;
	*width = 0;
	*min = 1000;
	if (!string)
		return ;
	while (string[i])
	{
		size = ft_strlen(string[i]);
		if (size > *width)
			*width = size;
		if (size < *min)
			*min = size;
		(*height)++;
		i++;
	}
}

bool	check_size(char **map)
{
	int	height;
	int	width;
	int	min;

	count_dimensions(map, &height, &width, &min);
	if (height < 3 || width < 3 || min < 3)
		return (false);
	return (true);
}

char	*join_free(char *string, char *add)
{
	char	*tmp;

	if (!string)
		return (ft_strdup(add));
	tmp = string;
	string = ft_strjoin(string, add);
	free(tmp);
	free(add);
	return (string);
}
