/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:26 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 11:02:27 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_line_tab(t_shell *shell, int i)
{
	char	**tmp;

	tmp = shell->list_cmd->arg;
	while (tmp[i + 2])
	{
		free(tmp[i]);
		tmp[i] = tmp[i + 2];
		tmp[i + 2] = NULL;
		i++;
	}
	tmp[i] = NULL;
}

void	fill_in(t_shell *shell, int i)
{
	char	**tmp;

	tmp = shell->list_cmd->arg;
	if (tmp[i][0] == '<' && tmp[i][0] == tmp[i][1])
	{
		here_doc(tmp[i + 1]);
		shell->list_cmd->redir_in = open(".here_doc", O_RDONLY);
	}
	else if (tmp[i][0] == '<')
		shell->list_cmd->redir_in = open(tmp[i + 1], O_RDONLY);
	if (shell->list_cmd->redir_in == -1)
		shell->quit = 1;
	delete_line_tab(shell, i);
}

void	fill_out(t_shell *shell, int i)
{
	char	**tmp;

	tmp = shell->list_cmd->arg;
	if (tmp[i][0] == '>' && tmp[i][0] == tmp[i][1])
		shell->list_cmd->redir_out = open(tmp[i + 1], \
		O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (tmp[i][0] == '>')
		shell->list_cmd->redir_out = open(tmp[i + 1], \
		O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	delete_line_tab(shell, i);
}

void	ft_fill_redir(t_shell *shell)
{
	t_list_cmd	*tmp;
	int			i;

	tmp = shell->list_cmd;
	while (shell->list_cmd)
	{
		i = 0;
		while (shell->list_cmd->arg[i])
		{
			if (!shell->list_cmd->arg[i + 1])
			{
				shell->list_cmd = tmp;
				return ;
			}	
			else if (shell->list_cmd->arg[i][0] == '>')
				fill_out(shell, i--);
			else if (shell->list_cmd->arg[i][0] == '<')
				fill_in(shell, i--);
			i++;
		}
		shell->list_cmd = shell->list_cmd->next;
	}
	shell->list_cmd = tmp;
	print_list_cmd(shell->list_cmd);
}
