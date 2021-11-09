/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:13:02 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 11:23:40 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*src;
	int		i;
	int		y;

	i = -1;
	y = -1;
	src = ft_calloc((ft_strlen((char *)s1) + \
	ft_strlen((char *)s2) + 1), sizeof(char));
	if (!(src))
		return (0);
	if (s1)
	{	
		while (s1[++i])
			src[i] = s1[i];
	}
	if (s2)
	{
		while (s2[++y])
		{
			src[i] = s2[y];
			i++;
		}
		src[i] = '\0';
	}
	return (src);
}
