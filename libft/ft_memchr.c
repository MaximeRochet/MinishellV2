/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 18:10:34 by cmasse            #+#    #+#             */
/*   Updated: 2021/03/10 13:07:13 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*n_s;

	n_s = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	if (!c)
		return ((void *)s + ft_strlen((char *)s));
	while (i < n)
	{
		if (n_s[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
