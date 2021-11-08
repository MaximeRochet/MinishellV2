#include "../includes/minishell.h"

void	init_env(char **env, t_shell *shell)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(env[i], '=') + 1 \
					, ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i])));
		i++;
	}
	shell->tab_env = env;
	return ;
}

int	ft_valide_quote_str(t_shell *shell)
{
	int		i;
	char	i_str;
	char	*str;
	int		quote;

	quote = 0;
	i = 0;
	i_str = 0;
	str = ft_strdup(shell->str_cmd);
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
		i++;
	}
//	free(str);
	return (quote);
}

int	lstsize(t_list_cmd *lst_cmd)
{
	t_list_cmd	*tmp;
	int			i;

	tmp = lst_cmd;
	i = 0;
	tmp = lst_cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	parsing(t_shell *shell)
{
	char	**str_split;

	shell->str_cmd = find_redir(shell->str_cmd);
	if (ft_valide_quote_str(shell) == 1)
	{
		printf(": number of invalid quotes\n");
		return (-1);
	}
	if (ft_check_variable(shell, 0) == -1)
		return (-1);
	//replace pipes
	shell->str_cmd = ft_replace_pipe_str(shell->str_cmd, '|');
	//split par pipe
	str_split = ft_split(shell->str_cmd, '\200');
	//split arg
	ft_split_arg_str(shell, str_split);
	//taille de la liste
	ft_free(str_split);
	shell->size_list_cmd = lstsize(shell->list_cmd);
	//remplissage des redirections
	ft_fill_redir(shell);
	//suppression des quotes
	ft_remove_quote_cmd(shell);
	//remplissage de la commande
	ft_path_cmd(shell);
	if (shell->list_cmd->cmd == NULL && !is_builtin(shell->list_cmd->arg[0]))
		{
		if (ft_check_exist_path(shell) == -1)
		{
			printf("%s: command not found\n", shell->list_cmd->arg[0]);
			return (-1);
		}
	}
	return (0);
}
