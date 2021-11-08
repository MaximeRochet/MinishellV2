/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:13:02 by cmasse            #+#    #+#             */
/*   Updated: 2021/06/02 11:35:19 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*src;
	int		i;
	int		y;

	i = 0;
	y = 0;
	src = ft_calloc((ft_strlen((char *)s1) + \
	ft_strlen((char *)s2) + 1), sizeof(char));
	if (!(src))
		return (0);
	if(s1)
	while (s1[i])
	{
		src[i] = s1[i];
		i++;
	}
	if(s2)
	while (s2[y])
	{
		src[i] = s2[y];
		i++;
		y++;
	}
	src[i] = '\0';
	return (src);
}
