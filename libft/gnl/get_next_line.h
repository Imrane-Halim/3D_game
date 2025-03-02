/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihalim <ihalim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:52 by ihalim            #+#    #+#             */
/*   Updated: 2025/03/01 14:09:55 by ihalim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ftt_strlen(char *s);
int		ftt_strchr(char *s, int c);
char	*ftt_strjoin(char *leftovers, char *buffer);
char	*find_leftovers(int fd, char *leftovers);
char	*find_line(char *leftovers);
char	*find_next_leftovers(char *leftovers);
char	*ftt_strcpy(char *dst, const char *src);

#endif
