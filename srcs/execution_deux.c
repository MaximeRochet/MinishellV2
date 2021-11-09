/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_deux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:06:28 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 15:07:29 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process_start(t_shell *shell, int i)
{
	if (shell->list_cmd->redir_out)
		dup2(shell->list_cmd->redir_out, STDOUT_FILENO);
	else
		dup2(shell->pipes[i][1], STDOUT_FILENO);
	if (shell->list_cmd->redir_out)
		close(shell->list_cmd->redir_out);
	close (shell->pipes[i][1]);
	find_function_exit(shell);
}

void	child_process_middle(t_shell *shell, int i)
{
	if (shell->list_cmd->redir_in)
		dup2(shell->list_cmd->redir_in, STDIN_FILENO);
	else
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (shell->list_cmd->redir_out)
		dup2(shell->list_cmd->redir_out, STDOUT_FILENO);
	else
		dup2(shell->pipes[i][1], STDOUT_FILENO);
	if (shell->list_cmd->redir_in)
		close(shell->list_cmd->redir_in);
	if (shell->list_cmd->redir_out)
		close(shell->list_cmd->redir_out);
	close(shell->pipes[i][1]);
	close(shell->pipes[i - 1][0]);
	find_function_exit(shell);
}

void	child_process_end(t_shell *shell, int i)
{
	if (shell->list_cmd->redir_in)
		dup2(shell->list_cmd->redir_in, STDIN_FILENO);
	else
		dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	if (shell->list_cmd->redir_in)
		close(shell->list_cmd->redir_in);
	close(shell->pipes[i - 1][0]);
	close(shell->pipes[i][1]);
	close(shell->pipes[i][0]);
	find_function_exit(shell);
}

void	child_process(t_shell *shell, int i)
{
	if (i == 0)
		child_process_start(shell, i);
	else if (i != (shell->size_list_cmd - 1))
		child_process_middle(shell, i);
	else
		child_process_end(shell, i);
}
