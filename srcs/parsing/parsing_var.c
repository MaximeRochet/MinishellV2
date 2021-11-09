/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:29:17 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/09 16:51:12 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_paste_name_var(int start, char *var, t_shell *shell, int i)
{
	char	*str;
	int		y;
	int		end;

	str = (char *)ft_calloc(sizeof(char), \
	ft_strlen(shell->str_cmd) + ft_strlen(var));
	y = 0;
	while (++i < start)
		str[i] = shell->str_cmd[i];
	end = i;
	while (var[y])
	{
		str[i] = var[y];
		i++;
		y++;
	}
	while (shell->str_cmd[end])
	{
		str[i] = shell->str_cmd[end];
		i++;
		end++;
	}
	shell->str_cmd = str;
	return (str);
}

char	*ft_delete_var(int start, int end, t_shell *shell)
{
	char	*str;
	int		i;

	str = (char *)calloc(sizeof(char), \
	start + ft_strlen(shell->str_cmd) - end);
	i = 0;
	while (i < start)
	{
		str[i] = shell->str_cmd[i];
		i++;
	}
	while (shell->str_cmd[i])
	{
		str[i] = shell->str_cmd[end];
		i++;
		end++;
	}
	str[i] = '\0';
	shell->str_cmd = str;
	return (str);
}

void	ft_replace_var(t_shell *shell, int i, int y)
{
	char	*str;
	char	*var;
	int		count;

	str = ft_strdup(shell->str_cmd);
	var = NULL;
	count = 0;
	i = i + 1;
	y = i;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
		i++;
		count++;
	}
	var = ft_strdup(ft_get_env(shell, ft_substr(str, y, count)));
	if (!var)
	{
		str = ft_strdup(ft_delete_var(y - 1, i, shell));
		shell->str_cmd = str;
		return ;
	}
	str = ft_strdup(ft_delete_var(y - 1, i, shell));
	str = ft_strdup(ft_paste_name_var(y - 1, var, shell, -1));
	shell->str_cmd = str;
	free(str);
}

int	ft_check_variable(t_shell *shell, int i)
{
	char	*str;
	int		d_quote;
	int		quote;

	d_quote = 0;
	str = shell->str_cmd;
	quote = 0;
	while (str[i])
	{	
		if (str[i] == '\"' && quote == 0)
			d_quote++;
		if (str[i] == '\'' && quote == 0 && d_quote % 2 == 0)
			quote = 1;
		else if (str[i] == '\'')
			quote = 0;
		if (str[i] == '$' && quote == 0 && str[i + 1] != '?' && str[i + 1])
		{
			ft_replace_var(shell, i, 0);
			if (shell->str_cmd && ft_strlen(shell->str_cmd) == 0)
				return (-1);
			str = ft_strdup(shell->str_cmd);
		}
		i++;
	}
	return (0);
}
