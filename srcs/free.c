/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:15:22 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 16:40:37 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
			free(s[i++]);
		free(s);
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->prompt)
	{
		free(shell->prompt);
		shell->prompt = NULL;
	}
	if (shell->str_cmd)
	{
		free(shell->str_cmd);
		shell->str_cmd = NULL;
	}
	if (shell->list_cmd)
	{
		while (shell->list_cmd)
		{
			free(shell->list_cmd->cmd);
			ft_free(shell->list_cmd->arg);
			shell->list_cmd = shell->list_cmd->next;
		}
	}
}
