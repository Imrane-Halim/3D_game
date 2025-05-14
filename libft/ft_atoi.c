/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:31:50 by ihalim            #+#    #+#             */
/*   Updated: 2025/05/13 10:23:51 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *s)
{
	long	res;
	int		sign;

	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	res = 0;
	while (*s >= '0' && *s <= '9')
	{
		if (res > (LONG_MAX - (*s - '0')) / 10)
			return (LONG_MAX);
		res = (res * 10) + (*s - '0');
		s++;
	}
	if (*s != '\0')
		return (LONG_MAX);
	return (res * sign);
}
