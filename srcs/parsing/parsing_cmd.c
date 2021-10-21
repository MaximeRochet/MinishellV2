/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:29:35 by cmasse            #+#    #+#             */
/*   Updated: 2021/10/19 16:30:53 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

//ENLEVER LES QUOTES DE LA COMMANDES 
// void	ft_remove_quote_cmd(t_shell *shell)
// {
// 	t_list_cmd *tmp_list;
// 	int i;
// 	int y;
// 	char *tmp_str;

// 	y = 0;
// 	tmp_list = shell->list_cmd;
// 	while (tmp_list)
// 	{
// 		i = 0;
// 		tmp_str = tmp_list->arg[0];
// 		while (tmp_str[i])
// 		{
// 			if (tmp_str[i]== '\'' ||tmp_str[i]== '\"' )
// 			{
// 				y = i;
// 				while (tmp_str[y])
// 				{
// 					tmp_str[y] = tmp_str[y + 1];
// 					y++;
// 				}
// 				tmp_str[y] = '\0';
// 			}
// 			i++;
// 		}
// 		tmp_list->cmd = tmp_str;
// 		tmp_list = tmp_list->next;
// 	}

// 	dprintf(1,"_________NV MAILLON AVEC PATH________\n");
// }



//SAVOIR S IL Y A DES QUOTE IMPAIRE OU DEDANS 
// void	ft_parsing_quote_cmd(t_shell *shell)
// {
// 	int quote;
// 	int i;
// 	char tmp;
// 	t_list_cmd *tmp_list;
// 	char *tmp_str;

// 	quote = 0;
// 	tmp = '\0';
// 	tmp_list = shell->list_cmd;
// 	while (tmp_list)
// 	{
// 		i = 0;
// 		tmp_str = tmp_list->arg[0];
// 		while (tmp_str[i])
// 		{
// 			if (tmp_str[i] == '\'' || tmp_str[i] == '\"')
// 			{
// 				if (quote == 0)
// 				{
// 					quote = 1;
// 					tmp = tmp_str[i];
// 				}
// 				else if (quote == 1 && tmp == tmp_str[i])
// 					quote = 0;
// 				else
// 				{
// 					printf("FAUX\n");
// 					return ;
// 				}
// 			}
// 			i++;
// 		}
// 		tmp_list = tmp_list->next;
// 		if (quote == 0)
// 			ft_remove_quote_cmd(shell);
// 	}
// 	return ;
// }

//VOIR SI LE CHEMIN DE PATH ET COMMANDE EXISTE 
void	ft_parsing_cmd(t_shell *shell)
{
	int i;
	t_list_cmd	*first;

	first = shell->list_cmd;
	i = 0;
	while (first)
	{
		i = 0;
		while (shell->path[i])
		{
		//	shell->list_cmd->cmd = ft_strtrim(shell->list_cmd->cmd, " ");

	//	dprintf(1,"shell->path[%d] = %s\n", i , shell->path[i]);
	//	dprintf(1, "shell->list->cmd = %s\n", shell->list_cmd->cmd);
			shell->path_cmd = ft_strjoin(shell->path[i], first->cmd );
	//	dprintf(1, "shell->path_cmd  = %s\n", shell->path_cmd );

			if (access(shell->path_cmd, F_OK) == 0)
			{
				first->cmd = ft_strdup(shell->path_cmd);
				if (first->next == NULL)
					return ;
				break ;
			}
			if (i == 6 && access(shell->path_cmd, F_OK) == -1)
			{
				first->cmd = "\0";
				return ;
			}
			i++;
		}
		first = first->next;
	}
	return ;
}