/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:39:19 by mrochet           #+#    #+#             */
/*   Updated: 2021/10/20 17:40:01 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int find_function(t_shell *shell)
{
	t_fonc	tab_f[] = {
		{"cd", &fonction_cd}, {"echo", &fonction_echo}, \
		{"env", &fonction_env}, {"export", &fonction_export}, \
		{"pwd", &fonction_pwd}, {"unset", &fonction_unset}, \
	   	{"execve", &fonction_execve}};
	int		i;
	char 	*cmd;

	cmd = shell->list_cmd->arg[0];

	i = 0;
	while (ft_strncmp(tab_f[i].name, cmd, 3) != 0 &&  ft_strncmp(tab_f[i].name, "execve", 3) != 0 )
		i++;
	tab_f[i].fct(shell);
	return(0);
}

int execution(t_shell *shell)
{
	find_function(shell);
	return(0);
}
