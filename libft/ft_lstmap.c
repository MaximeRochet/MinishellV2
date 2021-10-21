/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 15:37:54 by cmasse            #+#    #+#             */
/*   Updated: 2020/12/06 11:40:07 by cmasse           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n;
	t_list	*b;

	b = NULL;
	n = b;
	while (lst)
	{
		b = ft_lstnew((*f)(lst->content));
		if (!b)
		{
			ft_lstclear(&n, (*del));
			return (NULL);
		}
		ft_lstadd_back(&n, b);
		lst = lst->next;
	}
	return (n);
}
