/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:19:47 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/19 17:22:07 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_paste_name_var(int start, char *var, t_shell *shell)
{

	char *str;
	int i;
	int y;
	int end;

	str = (char *)calloc(sizeof(char), ft_strlen(shell->str_cmd) + ft_strlen(var));
	i = 0;
	y = 0;
	while (i < start)
	{
		str[i] = shell->str_cmd[i];
		i++;
	}
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
	char *str;
	int i;
//	char *tmp;

	str = (char *)calloc(sizeof(char), start + ft_strlen(ft_substr(shell->str_cmd, end, ft_strlen(shell->str_cmd))) + 1);
	// dprintf(1, "start=|%d|, str[start]=|%c|\n", start, str[start]);
	// dprintf(1, "end=|%d|, str[end]=|%c|\n", end, str[end]);
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

void ft_replace_var(t_shell *shell, int i)
{
	t_list_env *env;
	char *str;
	char *var;
	int y;
	int count;

	str = ft_strdup(shell->str_cmd);
	env = shell->env;
	var = NULL;
	count = 0;
	i = i + 1;
	y = i;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
	{
		i++;
		count++;
	}
	var = (char *)calloc(sizeof(char),count);
	var = ft_strdup(ft_get_env(shell, ft_substr(str, y, count)));
	if (!var)
	{
		str = ft_strdup(ft_delete_var(y - 1, i, shell));
		shell->str_cmd = str;
		return ;
	}
	str = ft_strdup(ft_delete_var(y - 1, i, shell));
	str = ft_strdup(ft_paste_name_var(y - 1, var ,shell));
//	printf("coucou\n");
	shell->str_cmd = str;
}

void ft_check_variable(t_shell *shell)
{
	int i;
	char *str;
	int d_quote;
	int quote;
	
	i = 0;
	d_quote = 0;
	str = shell->str_cmd;
	quote = 0;
	//print_shell(shell);
	while (str[i])
	{	
		if(str[i] == '\"' && quote == 0)
			d_quote++;
		if (str[i] == '\'' && quote == 0 && d_quote % 2 == 0)
			quote = 1;
		else if (str[i] == '\'')
			quote = 0;
		if (str[i] == '$' && quote == 0)
		{
			ft_replace_var(shell, i);
			str = ft_strdup(shell->str_cmd);
		}
		i++;
	}
	return ;
}