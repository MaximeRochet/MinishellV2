/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerisemasse <cerisemasse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:52:00 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/22 15:15:18 by cerisemasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_list_cmd(t_list_cmd *list_cmd)
{
	int i;
	int y = 0;
	t_list_cmd *tmp;

	tmp = list_cmd;
 	if (tmp)
 	{
 		while(tmp)
 		{
			dprintf(1, "____LIST MAILLON %d_____\n", y);
 			dprintf(1, "cmd = |%s|\npipe = %d \n", (*tmp).cmd, (*tmp).pipe);
			i =0;
 			while (tmp->arg[i])
			{
				dprintf(1, "arg[%d] = |%s|\n", i, tmp->arg[i]);
				i++;
			}
			i = 0;
			if (tmp->input)
			{
				while (tmp->input[i])
				{
					dprintf(1, "input[%d] = |%s|\n", i, tmp->input[i]);
					i++;
				}
			}
			i = 0;
			if (tmp->output)
			{
				while (tmp->output[i])
				{
					dprintf(1, "output[%d] = |%s|\n", i, tmp->output[i]);
					i++;
				}
			}
			tmp = tmp->next;
			y++;
			dprintf(1, "_________________\n");
 		}
 	}
}

void	print_shell(t_shell *shell)
{
	t_list_env *tmp;

	tmp = shell->env;
	dprintf(1, "____LIST SHELL____\n");
	dprintf(1, "__ENV__\n");
	while (tmp)
	{
		dprintf(1, "%s=%s\n", tmp->name, tmp->content) ;
		tmp = tmp->next;
	}
	dprintf(1,"_________________\n");
}

// void	print_env(t_list_env *lst)
// {
// 	t_list_env *n;

// 	n = lst;
	
// 	dprintf(1, "____LIST SHELL____\n");
// 	dprintf(1, "__ENV__\n");
// 	while (n)
// 	{
// 		dprintf(1, "%s=%s\n", n->name, n->content);
// 		n = n->next;
// 	}
// 	dprintf(1,"_________________\n");
// }
