/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:01:49 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 11:02:15 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_quote_cmd_next(char *tmp_str, int a, int y, int j)
{
	int	quote;

	quote = 0;
	while (tmp_str[y])
	{
		if ((tmp_str[y] == '\'' || tmp_str[y] == '\"') && quote == 0)
		{
			quote = 1;
			j = y;
			y++;
		}
		if (quote == 1 && tmp_str[j] == tmp_str[y])
		{
			y--;
			a = y;
			while (tmp_str[j++])
				tmp_str[j - 1] = tmp_str[j];
			while (tmp_str[y++])
				tmp_str[y - 1] = tmp_str[y];
			quote = 0;
			y = a - 1;
		}
		y++;
	}
}

void	ft_remove_quote_cmd(t_shell *shell)
{
	t_list_cmd	*tmp_list_cmd;
	int			i;
	int			y;
	int			j;
	char		*tmp_str;

	y = 0;
	j = 0;
	tmp_list_cmd = shell->list_cmd;
	while (tmp_list_cmd)
	{
		i = 0;
		while (tmp_list_cmd->arg[i])
		{
			tmp_str = tmp_list_cmd->arg[i];
			y = 0;
			ft_remove_quote_cmd_next(tmp_str, i, y, j);
			i++;
		}
		tmp_list_cmd = tmp_list_cmd->next;
	}
}

int	ft_check_exist_path(t_shell *shell)
{
	t_list_cmd	*tmp_str;
	int			i;

	i = 0;
	tmp_str = shell->list_cmd;
	while (tmp_str)
	{
		if (access(tmp_str->arg[0], F_OK) == 0 && \
		tmp_str->arg[0][ft_strlen(tmp_str->arg[0]) - 1] != ' ')
		{
			tmp_str->cmd = ft_strdup(tmp_str->arg[0]);
			if (tmp_str->next == NULL)
				return (0);
			break ;
		}
		if (i == 6 && access(tmp_str->arg[0], F_OK) == -1)
		{
			tmp_str->cmd = NULL;
			return (-1);
		}
		tmp_str = tmp_str->next;
	}
	return (-1);
}

void	ft_path_cmd_next(int i, char **tab_path, t_list_cmd	*tmp_str)
{
	int		y;
	char	*path_cmd;

	y = 0;
	while (tab_path[y])
	{
		tab_path[y] = ft_strjoin(tab_path[y], "/" );
		path_cmd = ft_strjoin(tab_path[y], tmp_str->arg[i]);
		if (access(path_cmd, F_OK) == 0)
		{
			tmp_str->cmd = ft_strdup(path_cmd);
			if (tmp_str->next == NULL )
				return ;
			break ;
		}
		if (i == 6 && access(path_cmd, F_OK) == -1)
		{
			free(path_cmd);
			tmp_str->cmd = "\0";
			return ;
		}
		y++;
	}
}

void	ft_path_cmd(t_shell *shell)
{
	int			i;
	t_list_cmd	*tmp_lst;
	char		**tab_path;

	tmp_lst = shell->list_cmd;
	tab_path = ft_split(ft_get_env(shell, "PATH"), ':');
	i = 0;
	while (tmp_lst)
	{
		i = 0;
		while (tmp_lst->arg[i] && tmp_lst->cmd == NULL)
		{
			ft_path_cmd_next(i, tab_path, tmp_lst);
			i++;
		}
		tmp_lst = tmp_lst->next;
	}
	ft_free(tab_path);
	return ;
}
