/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkreter <nkreter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 01:29:07 by nkreter           #+#    #+#             */
/*   Updated: 2026/10/10 01:34:46 by nkreter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *stash[fd])
{
	char	*buf;
	ssize_t	bytes_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_needed(stash[fd]));
	while (include_nl(stash[fd]) == -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			return (free_needed(stash[fd]));
		}
		else if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		//printf("READ: %ld bytes -> [%s]\n", bytes_read, buf); 
		stash[fd] = ft_strjoin(stash[fd], buf);
		if (!stash[fd])
			return (free_needed(buf));
	}
	free(buf);
	return (stash[fd]);
}

static char	*take_line(char **stash[fd])
{
	char	*res;
	char	*tmp;
	int		len;

	len = include_nl(*stash[fd]);
	if (len == -1)
	{
		res = *stash[fd];
		*stash[fd] = NULL;
		return (res);
	}
	res = ft_substr(*stash[fd], 0, len);
	if (!res)
		return (free_needed(*stash[fd]));
	tmp = ft_substr(*stash[fd], len, ft_strlen(*stash[fd]));
	if (!tmp)
		return (free_needed(res));
	free(*stash[fd]);
	*stash[fd] = tmp;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*res;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_line(fd, stash[fd]);
	if (!stash[fd] || *stash[fd] == '\0')
	{
		stash[fd] = free_needed(stash[fd]);
		return (NULL);
	}
	res = take_line(&stash[fd]);
	if (!res)
		return (free_needed(stash[fd]));
	return (res);
}