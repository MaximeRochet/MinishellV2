/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_trois.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:07:37 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 19:16:43 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipex_next(t_shell *shell, int i)
{
	int	pid;

	while (shell->list_cmd)
	{
		shell->pipes[i] = ft_calloc(sizeof(int), 2);
		pipe(shell->pipes[i]);
		pid = fork();
		shell->pids[i] = pid;
		if (pid < 0)
			return ;
		else if (pid > 0)
		{
			close(shell->pipes[i][1]);
			ft_ret_values(shell, pid);
		}
		else
			child_process(shell, i);
		shell->list_cmd = shell->list_cmd->next;
		i++;
	}
}

void	pipex(t_shell *shell)
{
	t_list_cmd	*tmp;
	int			i;

	tmp = shell->list_cmd;
	i = 0;
	shell->pipes = ft_calloc(sizeof(int), shell->size_list_cmd + 1);
	shell->pids = ft_calloc(sizeof(int), shell->size_list_cmd);
	pipex_next(shell, i);
	shell->list_cmd = tmp;
	i = -1;
	while (++i < shell->size_list_cmd)
		waitpid(shell->pids[i], 0, 0);
}

int	execution(t_shell *shell)
{
	int	pid;

	pid = 0;
	if (is_builtin(shell->list_cmd->arg[0]) && shell->size_list_cmd == 1 && \
	shell->list_cmd->redir_out == 0 && shell->list_cmd->redir_in == 0)
		find_function(shell);
	else if (shell->size_list_cmd == 1)
	{
		pid = fork();
		if (pid < 0)
			return (0);
		else if (pid != 0)
		{
			ft_ret_values(shell, pid);
			return (0);
		}
		else
			find_function(shell);
	}
	else if (shell->size_list_cmd > 1)
		pipex(shell);
	return (0);
}
