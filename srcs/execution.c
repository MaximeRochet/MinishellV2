/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:37:52 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 11:58:41 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const t_fonc	g_tab_f[] = { \
	{"cd", &fonction_cd_exit}, {"echo", &fonction_echo_exit}, \
	{"env", &fonction_env_exit}, {"export", &fonction_export_exit}, \
	{"pwd", &fonction_pwd_exit}, {"unset", &fonction_unset_exit}, \
	{"execve", &fonction_execve}};

void	ft_replace_ret_values(t_shell *shell)
{
	int		i;
	int		j;
	char	*ret;
	char	*new_cmd;
	char	**tmp;

	tmp = shell->list_cmd->arg;
	i = 0;
	while (tmp[i])
	{
		if (ft_strstr(tmp[i], "$?"))
		{
			j = -1;
			ret = ft_itoa(shell->ret_value);
			new_cmd = ft_calloc(sizeof(char), ft_strlen(tmp[i]) \
			+ ft_strlen(ret) - 1);
			while (tmp[i][++j] != '$')
				new_cmd[j] = tmp[i][j];
			ft_strcat(new_cmd, ret);
			ft_strcat(new_cmd, ft_strchr(tmp[i], '?') + 1);
			free(tmp[i]);
			tmp[i] = new_cmd;
		}
		i++;
	}
}

int	is_builtin(char *s)
{
	if (ft_strncmp("cd", s, ft_strlen(s)) && \
	ft_strncmp("echo", s, ft_strlen(s)) && \
	ft_strncmp("env", s, ft_strlen(s)) && \
	ft_strncmp("export", s, ft_strlen(s)) && \
	ft_strncmp("pwd", s, ft_strlen(s)) && \
	ft_strncmp("unset", s, ft_strlen(s)))
		return (0);
	return (1);
}

void	find_function_exit(t_shell *shell)
{
	int		i;
	char	*cmd;

	cmd = shell->list_cmd->arg[0];
	i = 0;
	ft_replace_ret_values(shell);
	while (ft_strncmp(g_tab_f[i].name, cmd, \
	strlen(g_tab_f[i].name) + 1) != 0 && \
	ft_strcmp(g_tab_f[i].name, "execve") != 0)
		i++;
	g_tab_f[i].fct(shell);
}

int	init_dup_file(t_shell *shell)
{
	if (shell->list_cmd->redir_in > 0)
		dup2(shell->list_cmd->redir_in, STDIN_FILENO);
	if (shell->list_cmd->redir_out > 0)
		dup2(shell->list_cmd->redir_out, STDOUT_FILENO);
	if (shell->list_cmd->redir_out > 0 || shell->list_cmd->redir_in > 0)
		return (1);
	return (0);
}

int	find_function(t_shell *shell)
{
	t_fonc	tab_f[7];
	int		i;
	char	*cmd;

	tab_f = { \
	{"cd", &fonction_cd}, {"echo", &fonction_echo}, \
	{"env", &fonction_env}, {"export", &fonction_export}, \
	{"pwd", &fonction_pwd}, {"unset", &fonction_unset}, \
	{"execve", &fonction_execve}};
	init_dup_file(shell);
	cmd = shell->list_cmd->arg[0];
	i = (shell->list_cmd->redir_out > 0 || shell->list_cmd->redir_in > 0) * 6;
	ft_replace_ret_values(shell);
	while (ft_strncmp(tab_f[i].name, cmd, strlen(tab_f[i].name) + 1) != 0 && \
	ft_strcmp(tab_f[i].name, "execve") != 0)
		i++;
	tab_f[i].fct(shell);
	return (0);
}

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

void	pipex(t_shell *shell)
{
	t_list_cmd	*tmp;
	int			pid;
	int			i;

	tmp = shell->list_cmd;
	i = 0;
	shell->pipes = ft_calloc(sizeof(int), shell->size_list_cmd + 1);
	shell->pids = ft_calloc(sizeof(int), shell->size_list_cmd);
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
