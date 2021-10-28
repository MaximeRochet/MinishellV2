#include "../includes/minishell.h"
//securier i+un
void	delete_line_tab(t_shell *shell,int i)
{
	char **tmp;
	
	tmp = shell->list_cmd->arg;
	while(tmp[i + 2])
	{
		free(tmp[i]);
		tmp[i] = tmp[i + 2];
		tmp[i + 2] = NULL;
		i++;
	}
	tmp[i] = NULL;
}

void	fill_in(t_shell *shell, int i)
{
	char **tmp;

	tmp = shell->list_cmd->arg;
	if (tmp[i][0] == '<' && tmp[i][0] == tmp[i][1])
		shell->list_cmd->redir_in = 400;
	else if(tmp[i][0] == '<')
		shell->list_cmd->redir_in = 500;
	delete_line_tab(shell, i);
}

void	fill_out(t_shell *shell, int i)
{
	char **tmp;
	
	tmp = shell->list_cmd->arg;
	if (tmp[i][0] == '>' && tmp[i][0] == tmp[i][1])
		shell->list_cmd->redir_out = 300;
	else if(tmp[i][0] == '>')
		shell->list_cmd->redir_out = 200;
	delete_line_tab(shell, i);
}

void    ft_fill_redir(t_shell *shell)
{
	t_list_cmd *tmp;
	int i;

	tmp = shell->list_cmd;
	while(shell->list_cmd)
	{
		i=-1;
		while(shell->list_cmd->arg[++i])
		{
			if(shell->list_cmd->arg[i][0] == '>')
				fill_out(shell, i);
			else if(shell->list_cmd->arg[i][0] == '<')
				fill_in(shell, i);
		}
		shell->list_cmd = shell->list_cmd->next;
	}
	shell->list_cmd = tmp;
	print_list_cmd(shell->list_cmd);
}
