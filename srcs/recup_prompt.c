/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:01:26 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/20 18:42:55 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *shearch_in_env(t_list_env *env,char *name)
{
	t_list_env *tmp;
	tmp = env;
	while(ft_strncmp(tmp->name, name, ft_strlen(name) != 0) && tmp)
		tmp = tmp->next;
	if(tmp)
		return(tmp->content);
	else
		return("NOT FOUND IN ENV");
}

char	*last_folder(char *pwd)
{
	char	*ret;
	int		y;
	int		tmp;

	y = ft_strlen(pwd);
	while (pwd[y - 1] != '/')
		y--;
	tmp = (ft_strlen(pwd) - y);
	ret = ft_calloc(sizeof(char),tmp + 1);
	tmp = 0;
	while (pwd[y])
		ret[tmp++] = pwd[y++];
	return(ret);	
}

void	recup_prompt(t_shell *shell)
{
	char	*ret;
	char	*user;
	char	*folder;

	user = shearch_in_env(shell->env, "USER");
	folder = last_folder(shearch_in_env(shell->env, "PWD"));
	ret = calloc(sizeof(char), ft_strlen(user) + ft_strlen(folder) + 4);
	strcat(ret, user);
	strcat(ret, "-");
	strcat(ret, folder);
	free(folder);
	strcat(ret, " :");
	shell->prompt = ret;
}
