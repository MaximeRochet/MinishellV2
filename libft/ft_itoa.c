/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 17:23:12 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:20:25 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_size(long int nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
	{
		nbr *= -1;
		i = 1;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static char	*ft_putnbr(long int n, int i, char *tab)
{
	if (n < 0)
		n *= -1;
	if (n > 9)
		ft_putnbr(n / 10, i - 1, tab);
	tab[i] = n % 10 + '0';
	return (tab);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	n = (long int)n;
	i = ft_size(n);
	tab = ft_malloc(sizeof(char), i + 1);
	if (!(tab))
		return (0);
	tab[i] = '\0';
	tab = ft_putnbr(n, i - 1, tab);
	if (n < 0)
		tab[0] = '-';
	return (tab);
}
