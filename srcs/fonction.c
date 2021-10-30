
#include "../includes/minishell.h"

void	ft_ret_values(t_shell *shell, int pid)
{
	int status;
	char **tmp;
	char *cmd;

	tmp = shell->list_cmd->arg;
	cmd = shell->list_cmd->cmd;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if(access(cmd, F_OK) == -1 && !is_builtin(tmp[0]))
			shell->ret_value = 127;
		else 
			shell->ret_value =  WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		shell->ret_value = 128 + WTERMSIG(status);
	if (shell->ret_value == 2)
	{
		if (!tmp[1])
		{
			tmp[1] = ft_strdup(getenv("HOME"));
			tmp[2] = 0;
		}
		else if (tmp[1][0] == '~')
			tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
		chdir(tmp[1]);
	}
}

void fonction_env(t_shell *shell)
{
	printf("act_env\n");
	if(shell->list_cmd->arg[1])
		return ;
	t_list_env *tmp;
	tmp = shell->env;
	while(tmp)
	{
		printf("%s=%s\n",tmp->name, tmp->content);
		tmp=tmp->next;
	}
	exit(0);
}

void delete_env(t_shell *shell, char *name)
{
	t_list_env *tmp;
	t_list_env *tmp_prev;

	tmp = shell->env;
	tmp_prev = shell->env;

	while(tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if(tmp)
	{
		while(tmp_prev->next != tmp)
			tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = tmp_prev->next->next;
}

//ok
void fonction_export(t_shell *shell)
{
	printf("act_export\n");
	int i;
	char *arg;
	t_list_cmd *tmp;

	i = 1;
	tmp = shell->list_cmd;
	while(tmp->arg[i])
	{
		arg =  tmp->arg[i];
		if(char_is_in(arg, '=') && arg[0] != '=')
		{
			delete_env(shell, ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
			ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1\
						, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));	
		}
		i++;
	}
	exit(0);
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
	exit(0);
}

void fonction_pwd(t_shell *shell)
{
	printf("act_pwd\n");
	(void)shell;

	(void)shell;
	char *buf;
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	exit(0);
}

void fonction_echo(t_shell *shell)
{
	printf("act_echo\n");
	(void)shell;
	int i = 1;
	if(shell->list_cmd->arg[i])
	{
		i += (ft_strncmp(shell->list_cmd->arg[i], "-n", 3) == 0);
		while(shell->list_cmd->arg[i])
		{
			printf("%s",shell->list_cmd->arg[i]);
			i++;
			if(shell->list_cmd->arg[i])
				printf(" ");	
		}
		if(ft_strncmp(shell->list_cmd->arg[1], "-n", 3))
			printf("\n");
	}
	else
		printf("\n");
	exit(0);
}

void modif_env(t_shell *shell, char *name, char *new_content)
{
	t_list_env *tmp;

	tmp = shell->env;
	while(tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if(tmp)
	{
		//free(tmp->content);
		tmp->content = ft_calloc(ft_strlen(new_content),1);
		tmp->content =  new_content;
	}
}

void fonction_cd(t_shell *shell)
{
	char **tmp;

	tmp = shell->list_cmd->arg;
	if (!tmp[1])
	{
		tmp[1] = ft_strdup(getenv("HOME"));
		tmp[2] = 0;
	}
	else if (tmp[1][0] == '~')
		tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
	if (chdir(tmp[1]) == -1)
	{
		printf("ERROR CD\n");
		exit(1);
	}
	exit(2);
}

void fonction_execve(t_shell *shell)
{
	t_list_cmd *tmp;

	printf("act_execve\n");
	(void)shell;
	tmp = shell->list_cmd;
	if (execve(tmp->cmd, tmp->arg, shell->tab_env) == -1)
		exit(1);
}
