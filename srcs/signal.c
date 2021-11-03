/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:14:06 by cerisemasse       #+#    #+#             */
/*   Updated: 2021/11/03 15:46:31 by mrochet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		//rl_replace_line("", 0);
		dprintf(1, "\n");
		dprintf(1, "%s", recup_prompt());
	}
}
