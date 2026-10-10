/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkreter <nkreter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 01:29:07 by nkreter           #+#    #+#             */
/*   Updated: 2026/10/10 01:45:31 by nkreter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	{
		res = free_needed(res);
		return (NULL);
	}
	tmp = ft_substr(*stash, len, ft_strlen(*stash));
	if (!tmp)
		return (free_needed(res));
	free(*stash);
	*stash = tmp;
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
