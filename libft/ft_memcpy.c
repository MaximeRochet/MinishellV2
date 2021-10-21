/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:00:18 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/07 13:35:32 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*n_dst;
	const char	*n_src;

	n_dst = (char *)dst;
	n_src = (const char *)src;
	i = 0;
	if (n_dst == 0 && n_src == 0)
		return (0);
	while (i < len)
	{
		n_dst[i] = n_src[i];
		
		i++;
	}
	n_dst[i] = '\0';
	return (dst);
}
