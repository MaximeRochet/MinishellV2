/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:13:56 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 19:19:16 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:27:30 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 14:13:52 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ret_values_next(t_shell *shell, int pid)
{
	char	**tmp;

	tmp = shell->list_cmd->arg;
	(void)pid;
	if (!tmp[1])
	{
		tmp[1] = ft_strdup(getenv("HOME"));
		tmp[2] = 0;
	}
	else if (tmp[1][0] == '~')
		tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
}

void	ft_ret_values(t_shell *shell, int pid)
{
	int		status;
	char	**tmp;
	char	*cmd;

	tmp = shell->list_cmd->arg;
	cmd = shell->list_cmd->cmd;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (access(cmd, F_OK) == -1 && !is_builtin(tmp[0]))
			shell->ret_value = 127;
		else
			shell->ret_value = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		shell->ret_value = 128 + WTERMSIG(status);
	if (shell->ret_value == 2)
		ft_ret_values_next(shell, pid);
}

void	fonction_env(t_shell *shell)
{
	t_list_env	*tmp;

	shell->ret_value = 0;
	tmp = shell->env;
	if (shell->list_cmd->arg[1])
		return ;
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	delete_env(t_shell *shell, char *name)
{
	t_list_env	*tmp;
	t_list_env	*tmp_prev;

	tmp = shell->env;
	tmp_prev = shell->env;
	while (tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp)
	{
		while (tmp_prev->next != tmp)
			tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = tmp_prev->next->next;
}

int	exist_env(t_shell *shell, char *arg)
{
	t_list_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (strcmp(tmp->name, arg) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
