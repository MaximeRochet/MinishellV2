/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:16:16 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 19:09:32 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fonction_env_exit(t_shell *shell)
{
	t_list_env	*tmp;

	tmp = shell->env;
	if (shell->list_cmd->arg[1])
		return ;
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	exit(0);
}

void	fonction_export_exit_next(t_shell *shell, t_list_cmd *tmp, int i)
{
	char		*arg;

	while (tmp->arg[i])
	{
		arg = tmp->arg[i];
		if (verif_arg_env(arg) != 'a')
		{
			printf("%c caractere invalide\n", verif_arg_env(arg));
			exit(1);
		}
		else if (strchr(arg, '='))
		{
			delete_env(shell, ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
			ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1 \
						, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));
		}
		else if (exist_env(shell, arg) == 0)
			ft_add_back_env(&shell->env, ft_lstnew_env(NULL, arg));
		i++;
	}
}

void	fonction_export_exit(t_shell *shell)
{
	int			i;
	t_list_cmd	*tmp;
	t_list_env	*tmp_env;

	i = 1;
	tmp_env = shell->env;
	tmp = shell->list_cmd;
	if (!tmp->arg[i])
	{
		while (tmp_env)
		{
			if (tmp_env->content)
				printf("declare -x %s=\"%s\"\n", tmp_env->name, tmp_env->content);
			else
				printf("declare -x %s\n", tmp_env->name);
			tmp_env = tmp_env->next;
		}
	}
	fonction_export_exit_next(shell, tmp, i);
	exit(0);
}

void	fonction_unset_exit(t_shell *shell)
{
	int	i;

	(void)shell;
	i = -1;
	if (!shell->list_cmd->arg[1])
		exit(0);
	else if (verif_arg_env(shell->list_cmd->arg[0]) != 'a')
	{
		printf("%c caractere invalide\n", \
				verif_arg_env(shell->list_cmd->arg[0]));
		exit (1);
	}
	while (shell->list_cmd->arg[++i])
		delete_env(shell, shell->list_cmd->arg[i]);
	exit(0);
}

void	fonction_pwd_exit(t_shell *shell)
{
	char	*buf;

	(void)shell;
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	exit(0);
}
