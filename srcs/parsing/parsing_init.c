/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:38 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 18:54:35 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_env(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->tab_env)
	{
		while (env[i])
		{
			ft_add_back_env(&shell->env, ft_lstnew_env(\
			ft_strchr(env[i], '=') + 1, ft_substr(env[i], \
			0, ft_strchr(env[i], '=') - env[i])));
			i++;
		}
		shell->tab_env = env;
	}
	modif_env(shell, "SHLVL", ft_itoa(ft_atoi(ft_get_env(shell, "SHLVL")) + 1));
	return ;
}

int	ft_valide_quote_str(t_shell *shell)
{
	int		i;
	char	i_str;
	char	*str;
	int		quote;

	quote = 0;
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

int	lstsize(t_list_cmd *lst_cmd)
{
	t_list_cmd	*tmp;
	int			i;

	tmp = lst_cmd;
	i = 0;
	tmp = lst_cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	parsing(t_shell *shell)
{
	char	**str_split;

	shell->str_cmd = find_redir(shell->str_cmd);
	if (ft_valide_quote_str(shell) == 1)
	{
		printf(": number of invalid quotes\n");
		return (-1);
	}
	if (ft_check_variable(shell, 0) == -1)
		return (-1);
	shell->str_cmd = ft_replace_pipe_str(shell->str_cmd, '|');
	if (shell->str_cmd[0] == '\200')
	{
		printf("syntax error near unexpected token `|'\n");
		return (-1);
	}
	str_split = ft_split(shell->str_cmd, '\200');
	ft_split_arg_str(shell, str_split);
	ft_free(str_split);
	shell->size_list_cmd = lstsize(shell->list_cmd);
	ft_fill_redir(shell);
	ft_remove_quote_cmd(shell);
	ft_path_cmd(shell);
	return (0);
}
