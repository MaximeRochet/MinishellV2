/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 17:42:50 by cmasse            #+#    #+#             */
/*   Updated: 2021/05/05 10:13:55 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;

	ret = ft_malloc((int) size, (int)count);
	if (!(ret))
		return (0);
	ft_bzero(ret, count * size);
	return (ret);
}
