/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_deux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:11:58 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 14:29:43 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_arg_env(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	while (str[++i])
		if (!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=' && \
				!ft_isdigit(str[i]))
			return (1);
	return (0);
}

void	fonction_export_next(t_shell *shell, t_list_cmd *tmp, int i)
{
	char		*arg;

	while (tmp->arg[i])
	{
		arg = tmp->arg[i];
		if (verif_arg_env(arg) != 0)
		{
			shell->ret_value = 1;
			printf("export: '%s' : not a valid identifier\n", arg);
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

void	fonction_export(t_shell *shell)
{
	int			i;
	t_list_cmd	*tmp;
	t_list_env	*tmp_env;

	shell->ret_value = 0;
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
	fonction_export_next(shell, tmp, i);
}

void	fonction_unset(t_shell *shell)
{
	int	i;

	shell->ret_value = 0;
	(void)shell;
	i = -1;
	if (!shell->list_cmd->arg[1])
		return ;
	if (verif_arg_env(shell->list_cmd->arg[1]) != 0)
	{
		shell->ret_value = 1;
		printf("unset: '%s' : not a valid identifier\n", \
				shell->list_cmd->arg[1]);
	}
	while (shell->list_cmd->arg[++i])
		delete_env(shell, shell->list_cmd->arg[i]);
}

void	fonction_pwd(t_shell *shell)
{
	char	*buf;

	shell->ret_value = 0;
	(void)shell;
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
}
