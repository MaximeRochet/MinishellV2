/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:09:20 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/10/20 17:04:57 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_index_strchr(const char *s, int c)
{
	int				i;

	i = 0;
	if (!c)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return (&str[i]);
	while (str[i] != '\0')
	{
		if (str[i] != to_find[j])
			i++;
		while (str[i] == to_find[j])
		{
			i++;
			j++;
			if (to_find[j] == '\0')
				return (&str[i - j]);
		}
		j = 0;
	}
	return (0);
}

void	ft_get_path(t_shell *shell, char *name)
{
	t_list_env *tmp_path;
	char *tmp;
	int i;
	int y;
	
	i = 0;
	y = 0;
	tmp_path = shell->env; 
	while (tmp_path)
	{
		if (ft_strstr(tmp_path->name, name))
		{
			tmp = tmp_path->content;
			shell->path = ft_split(tmp, ':');
			// while (shell->path[i])
			// {
			// //	printf("path[%d]=%s\n", i, shell->path[i]);
			// 	i++;
			//}
		}
		tmp_path = tmp_path->next;
	}
	while (shell->path[i])
	{
		y = ft_strlen(shell->path[i]);
		shell->path[i][y] = '/';
		i++;
	}
	return ;
}

char	*ft_get_env(t_shell *shell, char *name)
{
	t_list_env *tmp_env;
	char *tmp;
	int i;
	int y;
	
	i = 0;
	y = 0;
	tmp = NULL;
	tmp_env = shell->env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->name, name, ft_strlen(name)))
			tmp = tmp_env->content;
		tmp_env = tmp_env->next;
	}
	return (tmp);
}

int char_is_in(char *str, char c)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if(str[i] == c)
			return(1);
	}
	return(0);
}
