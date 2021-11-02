/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:09:20 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/11/02 12:19:36 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	i = 0;
	if (s1_temp && s2_temp)
	{
		while (s1_temp[i] && s2_temp[i])
		{
			if (s1_temp[i] != s2_temp[i] || s1_temp[i] == '\0')
				return (s1_temp[i] - s2_temp[i]);
			i++;
		}
		return (0);
	}
	else
		return (1);
}

int	ft_index_strchr(const char *s, int c)
{
	int	i;

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

// void	ft_get_path(t_shell *shell, char *name)
// {
// 	t_list_env *tmp_path;
// 	char *tmp;
// 	int i;
// 	int y;
// 	i = 0;
// 	y = 0;
// 	tmp_path = shell->env; 
// 	while (tmp_path)
// 	{
// 		if (ft_strstr(tmp_path->name, name))
// 		{
// 			tmp = tmp_path->content;
// 			shell->path = ft_split(tmp, ':');
// 		}
// 		tmp_path = tmp_path->next;
// 	}
// 	while (shell->path[i])
// 	{
// 		y = ft_strlen(shell->path[i]);
// 		shell->path[i][y] = '/';
// 		i++;
// 	}
// 	return ;
// }

char	*ft_get_env(t_shell *shell, char *name)
{
	t_list_env	*tmp_env;
	char		*tmp;

	tmp = NULL;
	tmp_env = shell->env;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->name, name))
			tmp = tmp_env->content;
		tmp_env = tmp_env->next;
	}
	return (tmp);
}

int	char_is_in(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}
