/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:11:40 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/12 13:42:45 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *str, size_t n)
{
	int			i;

	i = 0;
	while (str[i] && n--)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		n;
	size_t		size;
	size_t		i;

	n = ft_strnlen(dst, dstsize);
	size = n;
	i = 0;
	if ((dstsize - n) == 0)
		return (size + ft_strlen((char *)src));
	while (src[i] && n < dstsize - 1)
	{
		dst[n] = src[i];
		i++;
		n++;
	}
	dst[n] = '\0';
	return (size + ft_strlen((char *)src));
}
