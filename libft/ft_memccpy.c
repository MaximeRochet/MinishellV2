/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:20:28 by cmasse            #+#    #+#             */
/*   Updated: 2020/11/29 13:46:11 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*n_dst;
	unsigned char	*n_src;
	size_t			i;

	i = 0;
	n_dst = (unsigned char *)dst;
	n_src = (unsigned char *)src;
	while (i < n)
	{
		n_dst[i] = n_src[i];
		if (n_src[i] == (unsigned char)c)
			return (n_dst + (i + 1));
		i++;
	}
	return (NULL);
}
