/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:58:59 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:52:15 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy2(char *src, size_t start)
{
	char	*line;
	int		i;

	i = 0;
	if (start > ft_strlen(src))
	{
		free(src);
		return (NULL);
	}
	line = ft_malloc((ft_strlen(src) - (start + 1)) + 1, sizeof(char));
	if (!(line))
		return (0);
	while (src[start + 1])
	{
		line[i] = src[start + 1];
		start++;
		i++;
	}
	line[i] = '\0';
	free(src);
	return (line);
}

char	*copy(char *src, size_t n)
{
	size_t	i;
	int		size;
	char	*new_src;

	i = 0;
	if (n > ft_strlen(src))
		size = ft_strlen(src);
	else
		size = n;
	new_src = ft_malloc(size + 1, sizeof(char));
	if (!(new_src))
		return (0);
	while (src[i] && i < n)
	{
		new_src[i] = src[i];
		i++;
	}
	new_src[i] = '\0';
	return (new_src);
}
