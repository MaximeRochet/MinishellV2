/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrochet <mrochet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:01:26 by mrochet           #+#    #+#             */
/*   Updated: 2021/11/08 15:33:01 by mrochet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recup_prompt(void)
{
	char	*ret;
	char	*user;
	char	*folder;

	user = getenv("USER");
	folder = ft_strrchr(getcwd(NULL, 0), '/');
	ret = ft_calloc(sizeof(char), ft_strlen(user) + ft_strlen(folder) + 4);
	strcat(ret, user);
	strcat(ret, "-");
	strcat(ret, folder + 1);
	strcat(ret, " :");
	return (ret);
}
