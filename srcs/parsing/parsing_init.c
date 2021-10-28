/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerisemasse <cerisemasse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:50:00 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/28 17:12:31 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_env(char **env, t_shell *shell)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(env[i], '=') + 1\
					, ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i])));
		i++;
	}
	shell->tab_env = env;
	return ;
}

int	ft_valide_quote_str(t_shell *shell)
{
	int	i;
	char i_str;
	char *str;
	int quote = 0;

	i = 0;
	i_str = 0;
	str = ft_strdup(shell->str_cmd);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == 0)
			{
				quote = 1;
				i_str = str[i];
			}
			else if (quote == 1 && i_str == str[i])
				quote = 0;
		}
		i++;
	}
	return (quote);
}

int lstsize(t_list_cmd *lst_cmd)
{
	t_list_cmd *tmp;
	tmp = lst_cmd;
	int i = 0;
	while(tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}


//INITIALISATION 
int parsing(t_shell *shell)
{
	char **str_split;

	shell->str_cmd = find_redir(shell->str_cmd);
	if (ft_valide_quote_str(shell) == 1)
		return (-1);
	ft_check_variable(shell);
	shell->str_cmd = ft_replace_pipe_str(shell->str_cmd, '|');
	str_split = ft_split(shell->str_cmd, '\200');
	ft_split_arg_str(shell, str_split);
	shell->size_list_cmd = lstsize(shell->list_cmd);

	ft_fill_redir(shell);
	ft_remove_quote_cmd(shell);
	ft_path_cmd(shell);
	if (shell->list_cmd->cmd ==  NULL)
		ft_check_exist_path(shell);
	return(0);
}
