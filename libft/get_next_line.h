/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:00:41 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:49:39 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

int		ft_istrchr(char *s, char c);
char	*copy(char *src, size_t n);
char	*ft_fstrjoin(char *s1, char *s2);
char	*copy2(char *src, size_t start);
int		get_next_line(int fd, char **line);

#endif
