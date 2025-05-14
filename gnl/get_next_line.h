/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:52 by ihalim            #+#    #+#             */
/*   Updated: 2025/05/12 17:44:28 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		my_strlen(char *s);
int		my_strchr(char *s, int c);
char	*my_strjoin(char *leftovers, char *buffer);
char	*find_leftovers(int fd, char *leftovers);
char	*find_line(char *leftovers);
char	*find_next_leftovers(char *leftovers);
char	*my_strcpy(char *dst, const char *src);

#endif
