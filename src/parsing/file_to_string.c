/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:50:06 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/05/03 12:43:03 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*my_malloc(char c, char *string)
{
	char	*new_string;
	int		len;
	int		i;

	i = 0;
	if (!string)
		len = 0;
	else
		len = ft_strlen(string);
	new_string = malloc(len + 2);
	if (!new_string)
		return (NULL);
	while (string && string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	new_string[i] = c;
	new_string[i + 1] = '\0';
	free(string);
	return (new_string);
}

char	*file_to_string(char *path)
{
	char	*content;
	char	tmp[1];
	int		b_read;
	int		fd;

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	b_read = read(fd, tmp, 1);
	while (b_read > 0)
	{
		content = my_malloc(tmp[0], content);
		if (!content)
			return (NULL);
		b_read = read(fd, tmp, 1);
	}
	close(fd);
	return (content);
}
