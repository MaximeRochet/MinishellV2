/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:03:31 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/02 12:48:20 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*root;

	(void)root;
	root = *lst;
	while (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		ft_lstdelone(tmp, (*del));
	}
	root = NULL;
}
