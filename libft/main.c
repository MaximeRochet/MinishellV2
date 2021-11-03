/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:48:00 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/02 12:48:09 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int				i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_temp[i] != s2_temp[i] || s1_temp[i] == '\0')
			return (s1_temp[i] - s2_temp[i]);
		i++;
	}
	return (0);
}
