/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkreter <nkreter@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 23:59:36 by nkreter           #+#    #+#             */
/*   Updated: 2026/10/02 00:50:12 by nkreter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

size_t	ft_strlen(const char *s);
int		include_eol(char *s);	
char	*ft_strndup(const char *str, size_t n);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*free_needed(char *str);

#endif