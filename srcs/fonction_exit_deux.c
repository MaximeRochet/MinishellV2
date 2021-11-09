/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_exit_deux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:29:28 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 14:37:24 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fonction_echo_exit(t_shell *shell)
{
	int	i;

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
	exit(0);
}

void	fonction_cd_exit_next(char **tmp)
{
	printf(": cd: %s: No such file or directory\n", tmp[1]);
	exit(1);
}

void	fonction_cd_exit(t_shell *shell)
{
	char	**tmp;
	char	*old;
	int		ret;

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
		fonction_cd_exit_next(tmp);
	exit(0);
}
