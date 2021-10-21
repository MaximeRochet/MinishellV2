/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:46:14 by cmasse            #+#    #+#             */
/*   Updated: 2021/03/10 13:07:37 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	if (!c)
		return ((char *)s + ft_strlen((char *)s));
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)(s += i));
		i++;
	}
	return (0);
}
