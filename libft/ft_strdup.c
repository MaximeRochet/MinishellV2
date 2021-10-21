/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:22:01 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/19 18:43:11 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t		i;
	size_t		size;
	char		*n_src;

	i = 0;
	if (!src)
		return (NULL);
	size = ft_strlen((char *)src);
	n_src = ft_malloc(size + 1, sizeof(char));
	if (!(n_src))
		return (0);
	while (src[i])
	{
		n_src[i] = src[i];
		i++;
	}
	n_src[i] = '\0';
	return (n_src);
}
