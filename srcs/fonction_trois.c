/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_trois.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:30:09 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 14:30:14 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fonction_echo(t_shell *shell)
{
	int	i;

	shell->ret_value = 0;
	(void)shell;
	i = 1;
	if (shell->list_cmd->arg[i])
	{
		i += (ft_strncmp(shell->list_cmd->arg[i], "-n", 3) == 0);
		while (shell->list_cmd->arg[i])
		{
			printf("%s", shell->list_cmd->arg[i]);
			i++;
			if (shell->list_cmd->arg[i])
				printf(" ");
		}
		if (ft_strncmp(shell->list_cmd->arg[1], "-n", 3))
			printf("\n");
	}
	else
		printf("\n");
}

void	modif_env(t_shell *shell, char *name, char *new_content)
{
	t_list_env	*tmp;

	tmp = shell->env;
	while (tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp)
	{
		tmp->content = ft_calloc(ft_strlen(new_content), 1);
		tmp->content = new_content;
	}
}

void	fonction_cd_next(t_shell *shell, char **tmp)
{
	shell->ret_value = 1;
	printf(": cd: %s: No such file or directory\n", tmp[1]);
}

void	fonction_cd(t_shell *shell)
{
	char	**tmp;
	char	*old;
	int		ret;

	shell->ret_value = 0;
	old = getcwd(NULL, 0);
	tmp = shell->list_cmd->arg;
	(void)shell;
	if (!tmp[1] || ft_strncmp(tmp[1], "~", 2) == 0)
		ret = chdir(ft_get_env(shell, "HOME"));
	else
		ret = chdir(tmp[1]);
	modif_env(shell, "OLDPWD", old);
	modif_env(shell, "PWD", getcwd(NULL, 0));
	tmp = shell->list_cmd->arg;
	if (!tmp[1])
	{
		tmp[1] = ft_strdup(getenv("HOME"));
		tmp[2] = 0;
	}
	else if (tmp[1][0] == '~')
		tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
	if (ret == -1)
		fonction_cd_next(shell, tmp);
}

void	fonction_execve(t_shell *shell)
{
	t_list_cmd	*tmp;

	shell->ret_value = 0;
	if (shell->list_cmd->arg[0] == NULL || \
			!strncmp(shell->list_cmd->arg[0], "exit", 5))
		exit (1);
	if (shell->list_cmd->cmd == NULL && !is_builtin(shell->list_cmd->arg[0]))
	{
		if (ft_check_exist_path(shell) == -1)
			printf("%s: command not found\n", shell->list_cmd->arg[0]);
	}
	init_dup_file(shell);
	tmp = shell->list_cmd;
	if (execve(tmp->cmd, tmp->arg, shell->tab_env) == -1)
		exit(1);
}
