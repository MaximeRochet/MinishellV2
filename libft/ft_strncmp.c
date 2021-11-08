/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:56:37 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:33:28 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	i = 0;
	if(!s2 || n <= 0)
		return(1);
	while (i < n)
	{
		if (s1_temp[i] != s2_temp[i] || s1_temp[i] == '\0')
			return (s1_temp[i] - s2_temp[i]);
		i++;
	}
	return (0);
}
