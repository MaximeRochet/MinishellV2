/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:02:54 by cmasse            #+#    #+#             */
/*   Updated: 2020/11/29 13:43:04 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)s;
	if (n == 0)
		return ;
	while (i < n)
	{
		new[i] = 0;
		i++;
	}
}
