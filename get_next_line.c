/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:06:12 by wcapt             #+#    #+#             */
/*   Updated: 2024/10/23 17:22:01 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	read(int fd, void *buf, size_t count)
{
	return ();
}

char	*get_next_line(int fd)
{
	char	*line;
	static char	buffer[BUFFER_SIZE];
	int	i;

	i = 0;
	fd = open("get_next_line.txt", O_RDONLY);
	line = malloc(sizeof());
	if (!line)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
    while (i < bytes_read) {
        total_length++;
        char *new_line = realloc(line, total_length + 1);
        if (!new_line) {
            free(line);
            return NULL;
        }

        line = new_line;
        line[total_length - 1] = buffer[i];

        if (buffer[i] == '\n') {
            line[total_length] = '\0';
            return line;
        }

        i++;
    }
}

	return (line);
}

