/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:51:38 by imrane            #+#    #+#             */
/*   Updated: 2025/05/14 10:51:59 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// --- common utils
void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr[i]);
	free(arr);
}

int	count_args(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

bool	is_in_arr(char *value, const char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], value, ft_strlen(value)))
			return (true);
		i++;
	}
	return (false);
}

char	**add_line_to_arr(char **arr, char *line)
{
	char	**new;
	int		size;

	size = count_args(arr);
	new = malloc(sizeof(char *) * (size + 2));
	ft_memcpy(new, arr, sizeof(char *) * size);
	new[size] = line;
	new[size + 1] = NULL;
	free(arr);
	return (new);
}

// Search for a character in line matching condition
// find_type: 0 to find first char NOT in list, 1 to find first char IN list
char	*find_char_in_line(char *line, char *chars, int find_type)
{
	while (*line)
	{
		if ((ft_strchr(chars, *line) != NULL) == find_type)
			return (line);
		line++;
	}
	return (NULL);
}
