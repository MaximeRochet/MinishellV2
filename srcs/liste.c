/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:21:16 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/11/02 12:46:23 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list_cmd	*ft_new_cmd(char **arg)
{
	t_list_cmd	*list;

	list = ft_calloc(sizeof(t_list_cmd), 1);
	if (!list)
		return (0);
	list->arg = arg;
	list->redir_in = 0;
	list->redir_out = 0;
	list->next = NULL;
	return (list);
}

void	ft_add_back_cmd(t_list_cmd **alst, t_list_cmd *new)
{
	t_list_cmd	*tmp;

	tmp = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = tmp;
}

t_list_env	*ft_lstnew_env(void *content, void *name)
{
	t_list_env	*n;

	n = ft_malloc(sizeof(t_list_env), 1);
	if (!(n))
		return (0);
	n->content = content;
	n->name = name;
	n->next = NULL;
	return (n);
}

void	ft_add_back_env(t_list_env **alst, t_list_env *new)
{
	t_list_env	*tmp;

	tmp = *alst;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	*alst = tmp;
}
