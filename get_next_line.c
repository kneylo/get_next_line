/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkreter <nkreter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 23:58:39 by nkreter           #+#    #+#             */
/*   Updated: 2026/10/09 00:12:05 by nkreter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_needed(stash));
	while (include_nl(stash) == -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			return (free_needed(stash));
		}
		else if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		//printf("READ: %ld bytes -> [%s]\n", bytes_read, buf); 
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free_needed(buf));
	}
	free(buf);
	return (stash);
}

static char	*take_line(char **stash)
{
	char	*res;
	char	*tmp;
	int		len;

	len = include_nl(*stash);
	if (len == -1)
	{
		res = *stash;
		*stash = NULL;
		return (res);
	}
	res = ft_substr(*stash, 0, len);
	if (!res)
		return (free_needed(*stash));
	tmp = ft_substr(*stash, len, ft_strlen(*stash));
	if (!tmp)
		return (free_needed(res));
	free(*stash);
	*stash = tmp;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);	
	}
	res = take_line(&stash);
	if (!res)
		return (free_needed(stash));
	return (res);
}

/*pour tester visuellement
rajouter a ligne 34: printf("READ: %ld bytes -> [%s]\n", bytes_read, buf); 
int main(void)
{	
	int fd;
	int line_num;
	char *next_line;

	fd = open("giant_line.txt", O_RDONLY, 0644);
	if (fd == -1)
		return (printf("fd not opened\n"), 1);
	line_num = 1;
	printf("%d\n", BUFFER_SIZE);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		free(next_line);
		next_line = NULL;
		line_num++;
	}
	close(fd);
	return (0);
}*/