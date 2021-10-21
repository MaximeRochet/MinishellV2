/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 09:17:14 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/19 15:10:50 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_istrchr(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fstrjoin(char *s1, char *s2)
{
	char	*src;
	int		i;
	int		y;
	size_t	size;

	i = 0;
	y = -1;
	size = (ft_strlen(s1) + ft_strlen(s2));
	src = ft_malloc(size + 1, sizeof(char));
	if (!(src))
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			src[i] = s1[i];
			i++;
		}
	}
	while (s2[++y])
		src[i++] = s2[y];
	src[i] = '\0';
	free(s1);
	return (src);
}

int	get_next_line(int fd, char **line)
{
	char			buffer[100];
	static char		*stock;
	int				read_value;

	if (!line || read(fd, buffer, 0) < 0)
		return (-1);
	while (ft_istrchr(stock, '\n') == -1)
	{
		read_value = (read(fd, buffer, 1));
		if (read_value >= 0)
		{
			buffer[read_value] = '\0';
			stock = ft_fstrjoin(stock, buffer);
			if (!(stock))
				return (0);
			if (read_value == 0)
				break ;
		}
	}
	*line = copy(stock, ft_istrchr(stock, '\n'));
	stock = copy2(stock, ft_istrchr(stock, '\n'));
	if (stock == 0)
		return (0);
	return (1);
}
