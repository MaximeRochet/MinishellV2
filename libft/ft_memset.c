/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:35:01 by cmasse            #+#    #+#             */
/*   Updated: 2020/11/29 16:46:16 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*new;
	size_t	i;

	new = (char *)s;
	i = 0;
	while (i < n)
	{
		new[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
