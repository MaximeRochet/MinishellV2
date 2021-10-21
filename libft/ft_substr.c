/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:07:39 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:38:25 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	a;
	char	*n_s;
	size_t	size;

	a = 0;
	if (s == 0)
		return (0);
	if (start >= ft_strlen((char *)s))
		return (ft_calloc(1, 1));
	if ((ft_strlen((char *)s) - start) > len)
		size = len;
	else
		size = ft_strlen((char *)s) - start;
	n_s = ft_malloc(size + 1, sizeof(char));
	if (!(n_s))
		return (0);
	while (s[start] && a < len)
	{
		n_s[a] = s[start];
		start++;
		a++;
	}
	n_s[a] = '\0';
	return (n_s);
}
