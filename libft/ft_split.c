/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:16:44 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:27:14 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_nb_ligne(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != c)
		count = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return ((char **)ft_calloc(sizeof(char *), count + 1));
}

static char	**ft_words(char **str, char const *s, char c)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	x = 0;
	if (!str)
		return (0);
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			y++;
			i++;
		}
		if (y != 0)
			str[x++] = (char *)ft_calloc(sizeof(char), (y + 1));
		y = 0;
		while (s[i] == c && s[i])
			i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		y;
	int		x;
	char	**str;

	i = 0;
	y = 0;
	x = 0;
	if (!s)
		return (0);
	str = ft_words(ft_nb_ligne(s, c), s, c);
	if (!(str))
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			y = 0;
		while (s[i] != c && s[i])
			str[x][y++] = s[i++];
		x += 1;
	}
	return (str);
}
