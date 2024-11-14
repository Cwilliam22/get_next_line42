/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt <wcapt@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:06:12 by wcapt             #+#    #+#             */
/*   Updated: 2024/11/13 22:58:15 by wcapt            ###   ########.fr       */
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

char	*ft_put_line(char *str)
{
	char	*dst;
	size_t	i;
	size_t	size;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	size = i + 1;
	if (str[i] == '\n')
		size++;
	dst = malloc(sizeof(char) * size);
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		dst[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		dst[i++] = '\n';
	dst[i] = '\0';
	return (dst);
}

char	*read_and_store(int fd, char **line)
{
	ssize_t	count;
	char	*temp;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_condition(*line) == 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
		{
			if (count == -1 || (*line && **line == '\0'))
				return (free(*line), *line = NULL, free(buffer), NULL);
			break ;
		}
		buffer[count] = '\0';
		temp = *line;
		*line = ft_strjoin(*line, buffer);
		free(temp);
		if (!*line)
			return (free(buffer), NULL);
	}
	return (free(buffer), *line);
}

int	check_null(int fd, char **line)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (1);
	if (!*line)
	{
		*line = malloc(sizeof(char) * 1);
		if (!*line)
			return (1);
		(*line)[0] = '\0';
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*dst;
	char		*temp;

	if (check_null(fd, &line) || !read_and_store(fd, &line))
		return (NULL);
	dst = ft_put_line(line);
	if (!dst)
		return (NULL);
	temp = line;
	line = ft_strchr(line, '\n');
	if (line)
	{
		line = ft_strdup(line + 1);
		free(temp);
		if (!line)
			return (NULL);
	}
	else
	{
		free(temp);
		line = NULL;
	}
	return (dst);
}

/*
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

	int n = 20;

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
*/
