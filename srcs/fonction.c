
#include "../includes/minishell.h"

void fonction_env(t_shell *shell)
{
	printf("act_env\n");
	if(shell->list_cmd->arg[1])
		return ;
	t_list_env *tmp;
	tmp = shell->env;
	while(tmp)
	{
		if(tmp->name)
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
	t_list_env *tmp_env;

	i = 1;
	tmp_env = shell->env;
	tmp = shell->list_cmd;
	if(!tmp->arg[i])
		while(tmp_env)
		{
			if(tmp_env->content)
				printf("declare -x %s=\"%s\"\n",tmp_env->name, tmp_env->content);
			else
				printf("declare -x %s=\n",tmp_env->name);
			tmp_env = tmp_env->next;
		}
	while(tmp->arg[i])
	{
		arg =  tmp->arg[i];
		delete_env(shell, ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
		ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1\
			, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));	
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

	printf("%s\n", buf);
}

void fonction_echo(t_shell *shell)
{
	printf("act_echo\n");
	(void)shell;
	int i = 1;
	if(shell->list_cmd->arg[i])
	{
		i += (ft_strncmp(shell->list_cmd->arg[i], "-n", 3) == 0);
		printf("act_echo  %d \n", i);
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
	char *old;

	printf("act_cd\n");
	old = getcwd(NULL, 0);
	tmp = shell->list_cmd->arg;
	(void)shell;
	if(!tmp[1] || ft_strncmp(tmp[1], "~", 2) == 0)
		chdir(ft_get_env(shell, "HOME"));
	else if(tmp && tmp[1] && tmp[2])
		return ;
	else
		chdir(tmp[1]);
	modif_env(shell, "OLDPWD", old);
	modif_env(shell, "PWD", getcwd(NULL, 0));
	printf("old = %s\n", ft_get_env(shell, "OLDPWD"));
	printf("pwd = %s\n", ft_get_env(shell, "PWD"));

}

void fonction_execve(t_shell *shell)
{
	t_list_cmd *tmp;
	int pid;
	int status;

	printf("act_execve\n");
	(void)shell;
	tmp = shell->list_cmd;
	pid = fork();
	if (pid > 0) {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} 
	else
	{
		if (execve(tmp->cmd, tmp->arg, shell->tab_env) == -1)
			dprintf(1, "EXIT FAILED\n");
		exit(0);
	}
}
