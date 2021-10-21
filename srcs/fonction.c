/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:08:17 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/20 18:19:36 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:28:17 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/20 17:35:16 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//ok
void fonction_env(t_shell *shell)
{
	//env echo lolo
	if(shell->list_cmd->arg[1])
		return ;
	t_list_env *tmp;
	tmp = shell->env;
	while(tmp)
	{
		printf("%s=%s\n",tmp->name, tmp->content);
		tmp=tmp->next;
	}
}

void fonction_export(t_shell *shell)
{
	int i;
	char *arg;
	t_list_cmd *tmp;

	i = 1;
	tmp = shell->list_cmd;
	while(tmp->arg[i])
	{
		arg =  tmp->arg[i];
		printf("%d\n",(char_is_in(arg, '=') && arg[0] != '='));
		if(char_is_in(arg, '=') && arg[0] != '=')
		{
			ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1\
						, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));	
		}
		i++;
	}
}

void fonction_unset(t_shell *shell)
{
	(void)shell;
	/*t_list_env *tmp;

	  tmp = shell->env;
	  if(shell->list_cmd->arg[1])
	  return ;
	  while(shell->list_cmd->arg[1] != shell->env->next->name && shell->env->next)
	  shell->env = shell->env->next;

	  shell->env = tmp;
	  */
}

void fonction_pwd(t_shell *shell)
{
	(void)shell;
	char *buf;
	buf = getcwd(NULL, 0);

	printf("%s", buf);
}

void fonction_echo(t_shell *shell)
{
	(void)shell;
	printf("act_env\n");
}

void fonction_cd(t_shell *shell)
{
	(void)shell;
	printf("act_env\n");
}

void fonction_execve(t_shell *shell)
{
	t_list_cmd *tmp;
	int pid;
	int status;

	(void)shell;
	tmp = shell->list_cmd;
	pid = fork();
	if (pid > 0) {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} 
	else
	{
		if (execve(tmp->cmd, tmp->arg, NULL) == -1)
			dprintf(1, "EXIT FAILED\n");
		//exit(0);
	}
}
