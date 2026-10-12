/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkreter <nkreter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:02:39 by nkreter           #+#    #+#             */
/*   Updated: 2026/10/11 17:02:42 by nkreter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line;
	int		i;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	fd3 = open("test.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
		return (perror("open"), 1);
	i = 0;
	while (i < 5)
	{
		line = get_next_line(fd1);
		if (line)
		{
			printf("FD1: %s", line);
			free(line);
		}
		line = get_next_line(fd2);
		if (line)
		{
			printf("FD2: %s", line);
			free(line);
		}
		line = get_next_line(fd3);
		if (line)
		{
			printf("FD3: %s", line);
			free(line);
		}
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}