/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:36:51 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/26 18:05:39 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in(char const c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		a;
	int		size;
	char	*n;

	if (!s1)
		return (0);
	size = ft_strlen((char *)s1) - 1;
	i = 0;
	a = 0;
	while ((ft_is_in(s1[i], set) == 1 && s1[i]))
		i++;
	while (size > 0 && ft_is_in(s1[size], set) == 1)
		size--;
	if (size <= 0)
		return (ft_calloc(sizeof(char), 1));
	n = ft_malloc(size - i + 2, sizeof(char));
	if (!(n))
		return (0);
	while (i <= size)
		n[a++] = s1[i++];
	n[a] = '\0';
	return (n);
}

char	*ft_strftrim(char *s1, char const *set, int i, int a)
{
	int		size;
	char	*n;

	if (!s1)
		return (0);
	size = ft_strlen((char *)s1) - 1;
	if (size == 0)
		size = 1;
	while ((ft_is_in(s1[i], set) == 1 && s1[i]))
		i++;
	while (ft_is_in(s1[size], set) == 1 && size > 0)
		size--;
	if (size <= 0)
		return (ft_calloc(sizeof(char), 1));
	n = ft_malloc((size - i) + 1, sizeof(char));
	if (!(n))
		return (0);
	while (i <= size)
		n[a++] = s1[i++];
	n[a] = '\0';
	free(s1);
	return (n);
}
