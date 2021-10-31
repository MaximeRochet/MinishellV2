/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerisemasse <cerisemasse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:39:19 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/30 14:59:52 by cerisemasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_replace_ret_values(t_shell *shell)
{
	int 	i;
	int		j;
	char	*ret;
	char	*new_cmd;
	char **tmp;

	tmp = shell->list_cmd->arg;

	i = 0;
	while (tmp[i])
	{
		if (ft_strchr(tmp[i], '$'))
		{
			j = -1;
			ret = ft_itoa(shell->ret_value);
			new_cmd = ft_calloc(sizeof(char), ft_strlen(tmp[i]) + ft_strlen(ret) - 1);
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
	if(ft_strcmp("cd", s) && ft_strcmp("echo", s) && ft_strcmp("env", s) && ft_strcmp("export", s) && ft_strcmp("pwd", s) && ft_strcmp("unset", s))
		return (0);
	return (1);
}

int find_function(t_shell *shell)
{ 
	t_fonc	tab_f[] = {
		{"cd", &fonction_cd}, {"echo", &fonction_echo}, \
		{"env", &fonction_env}, {"export", &fonction_export}, \
		{"pwd", &fonction_pwd}, {"unset", &fonction_unset}, \
		{"execve", &fonction_execve}};
	int		i;
	char 	*cmd;

	cmd = shell->list_cmd->arg[0];
	i = 0;
	ft_replace_ret_values(shell);
	while (ft_strcmp(tab_f[i].name, cmd) != 0 &&
			ft_strcmp(tab_f[i].name, "execve") != 0)
	{
		i++;
	}
	tab_f[i].fct(shell);
	return(0);
}

void	child_process_start(t_shell *shell, int i)
{
	dup2(shell->pipes[i][1], STDOUT_FILENO);
	close (shell->pipes[i][1]);
	find_function(shell);
}

void	child_process_middle(t_shell *shell, int i)
{
	dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	dup2(shell->pipes[i][1], STDOUT_FILENO);
	close(shell->pipes[i][1]);
	close(shell->pipes[i - 1][0]);
	find_function(shell);
}

void	child_process_end(t_shell *shell, int i)
{
	dup2(shell->pipes[i - 1][0], STDIN_FILENO);
	close(shell->pipes[i - 1][0]);
	close(shell->pipes[i][1]);
	close(shell->pipes[i][0]);
	find_function(shell);
}

void	child_process(t_shell *shell, int i)
{
	//create fd
	if (i == 0)
		child_process_start(shell, i);
	else if (i != (shell->size_list_cmd - 1))
		child_process_middle(shell, i);
	else
		child_process_end(shell, i);
}

void	pipex(t_shell *shell)
{
	t_list_cmd *tmp;
	tmp = shell->list_cmd;
	int pid;
	int i;

	i = 0;
	shell->pipes =ft_calloc(sizeof(int), shell->size_list_cmd + 1);
	shell->pids = ft_calloc(sizeof(int), shell->size_list_cmd);
	while(shell->list_cmd)
	{
		shell->pipes[i] = ft_calloc(sizeof(int), 2);
		pipe(shell->pipes[i]);
		pid = fork();
		shell->pids[i] = pid;
		if(pid < 0)
			return;
		else if(pid > 0)
			close(shell->pipes[i][1]);
		else
			child_process(shell, i);
		shell->list_cmd = shell->list_cmd->next;
		i++;
	}
	shell->list_cmd = tmp;
	i = -1;
	while(++i < shell->size_list_cmd)
		waitpid(shell->pids[i],0,0);
}

int execution(t_shell *shell)
{
	int pid = 0;
	if(shell->size_list_cmd == 1)
	{
		pid = fork();
		if(pid < 0)
			return(0);
		else if(pid != 0)
		{
			ft_ret_values(shell, pid);
		//	waitpid(pid,0,0);
			return(0);
		}
		else
			find_function(shell);
	}
	else if(shell->size_list_cmd > 1)
		pipex(shell);
	dprintf(1,"PIPEX2\n");		
	return(0);
}


