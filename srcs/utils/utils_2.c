/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:18:48 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/02 12:20:02 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_strcat(char *dst, const char *src)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(dst);
	while (src[i])
	{
		dst[n] = src[i];
		i++;
		n++;
	}
	dst[n] = '\0';
}
