
#include "../includes/minishell.h"

//ok
void fonction_env(t_shell *shell)
{
	printf("act_env\n");
	//env echo lolo
	if(shell->list_cmd->arg[1])
		return ;
	t_list_env *tmp;
	tmp = shell->env;
	while(tmp)
	{
		printf("%s=%s\n",tmp->name, tmp->content);
		tmp=tmp->next;
	}
}

void delete_env(t_shell *shell, char *name)
{
	t_list_env *tmp;
	t_list_env *tmp_prev;

	tmp = shell->env;
	tmp_prev = shell->env;
	
	while(tmp && strcmp(tmp->name, name))
		tmp = tmp->next;
	if(tmp)
	{
		while(tmp_prev->next != tmp)
			tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = tmp_prev->next->next;
/*
	while(previous->next)
	{
		tmp = previous->next;
		//dprintf(1,"|%s| |%s|\n",tmp->name, name);
		if(strcmp(tmp->name, name) == 0 && tmp->next)
			previous->next = previous->next->next;
		else if(strcmp(tmp->name, name) == 0)
			previous->next  = NULL;
		previous = previous->next;
	}
*/
}

//ok
void fonction_export(t_shell *shell)
{
	int i;
	char *arg;
	t_list_cmd *tmp;

	printf("act_export\n");
	i = 1;
	tmp = shell->list_cmd;
	while(tmp->arg[i])
	{
		arg =  tmp->arg[i];
		printf("%d\n",(char_is_in(arg, '=') && arg[0] != '='));
		if(char_is_in(arg, '=') && arg[0] != '=')
		{
			delete_env(shell, ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
			ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1\
						, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));	
		}
		i++;
	}
}

void fonction_unset(t_shell *shell)
{
	printf("act_unset\n");
	(void)shell;

	int i = -1;
	if(!shell->list_cmd->arg[1])
		return ;
	while(shell->list_cmd->arg[++i])
		delete_env(shell,shell->list_cmd->arg[i]);
}

void fonction_pwd(t_shell *shell)
{
	printf("act_pwd\n");
	(void)shell;

	(void)shell;
	char *buf;
	buf = getcwd(NULL, 0);

	printf("%s", buf);
}

void fonction_echo(t_shell *shell)
{
	(void)shell;
	printf("act_echo\n");
}

void fonction_cd(t_shell *shell)
{
	(void)shell;
	printf("act_cd\n");
}

void fonction_execve(t_shell *shell)
{
	t_list_cmd *tmp;
	int pid;
	int status;

	printf("act_execve\n");
	(void)shell;
	(void)shell;
	tmp = shell->list_cmd;
	pid = fork();
	if (pid > 0) {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} 
	else
	{
		if (execve(tmp->cmd, tmp->arg, NULL) == -1)
			dprintf(1, "EXIT FAILED\n");
		//exit(0);
	}
}
