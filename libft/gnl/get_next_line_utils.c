/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:46 by ihalim            #+#    #+#             */
/*   Updated: 2025/03/01 14:09:37 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ftt_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ftt_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ftt_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ftt_strjoin(char *leftovers, char *buffer)
{
	char	*str;
	int		leftovers_len;
	int		buffer_len;

	if (buffer == NULL)
		return (NULL);
	if (!leftovers)
	{
		leftovers = (char *)malloc(1);
		if (!leftovers)
			return (NULL);
		leftovers[0] = '\0';
	}
	leftovers_len = ftt_strlen(leftovers);
	buffer_len = ftt_strlen(buffer);
	str = (char *)malloc(leftovers_len + buffer_len + 1);
	if (str == NULL)
	{
		free(leftovers);
		return (NULL);
	}
	ftt_strcpy(str, leftovers);
	ftt_strcpy(str + leftovers_len, buffer);
	free(leftovers);
	return (str);
}
