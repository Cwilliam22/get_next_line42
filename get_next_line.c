/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:06:12 by wcapt             #+#    #+#             */
/*   Updated: 2024/11/05 17:05:09 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_condition(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_jsp(char *str)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	while (j < i)
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	count;
	char	*dst;
	char	*temp;

	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (ft_condition(line) == 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
		{
			free(line);
			return (NULL);
		}
		if (count == 0)
			break ;
		buffer[count] = '\0';
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
		if (!line)
			return (NULL);
	}
	dst = ft_jsp(line);
	temp = line;
	line = ft_strchr(line, 10);
	if (line && *line == '\n')
		line++;
	else
		line = NULL;
	free(temp);
	return (dst);
}

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char *get_next_line(int fd);

int main(void)
{
    int fd = open("get_next_line.txt", O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    int n = 5;

    int i = 0;
    char *line;


    while (i < n) {
        line = get_next_line(fd);
        if (line) {
            printf("Ligne %d: %s\n", i + 1, line);
            free(line);
        } else {
            printf("Aucune ligne lue ou erreur lors de la ligne %d\n", i + 1);
        }
        i++;
    }
    close(fd);

    return 0;
}