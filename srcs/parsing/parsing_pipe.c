/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cerisemasse <cerisemasse@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:28:19 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/22 11:14:02 by cerisemasse      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_replace_pipe_str(char *str, char c)
{
	int	i;
	char i_str;
	int quote = 0;

	i = 0;
	i_str = 0;
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
		else if (quote == 0 && str[i] == c)
			str[i] = '\200';
		i++;
	}
	return (str) ;
}

void	ft_split_arg_str(t_shell *shell, char **str_split)
{
	int i;
	char	**split;

	i = 0;
	while (str_split[i])
	{
		ft_replace_pipe_str(str_split[i], ' ');
		split = ft_split(str_split[i], '\200');
		ft_add_back_cmd(&shell->list_cmd, ft_new_cmd(split));
		i++;
	}
	print_list_cmd(shell->list_cmd);
 }
