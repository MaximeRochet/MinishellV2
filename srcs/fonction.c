
#include "../includes/minishell.h"

void	ft_ret_values_next(t_shell *shell, int pid)
{
	char	**tmp;
	tmp = shell->list_cmd->arg;
	(void)pid;
	if (!tmp[1])
	{
		tmp[1] = ft_strdup(getenv("HOME"));
		tmp[2] = 0;
	}
	else if (tmp[1][0] == '~')
		tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
}

void	ft_ret_values(t_shell *shell, int pid)
{
	int		status;
	char	**tmp;
	char	*cmd;

	tmp = shell->list_cmd->arg;
	cmd = shell->list_cmd->cmd;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (access(cmd, F_OK) == -1 && !is_builtin(tmp[0]))
			shell->ret_value = 127;
		else
			shell->ret_value = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
		shell->ret_value = 128 + WTERMSIG(status);
	if (shell->ret_value == 2)
		ft_ret_values_next(shell, pid);
}

void	fonction_env(t_shell *shell)
{
	t_list_env	*tmp;

	tmp = shell->env;
	printf("act_env\n");
	if (shell->list_cmd->arg[1])
		return ;
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	delete_env(t_shell *shell, char *name)
{
	t_list_env	*tmp;
	t_list_env	*tmp_prev;

	tmp = shell->env;
	tmp_prev = shell->env;
	while (tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp)
	{
		while (tmp_prev->next != tmp)
			tmp_prev = tmp_prev->next;
	}
	tmp_prev->next = tmp_prev->next->next;
}

int exist_env(t_shell *shell, char *arg)
{
	t_list_env *tmp;

	tmp = shell->env;
	while(tmp)
	{
		if(strcmp(tmp->name, arg) == 0)
			return(1);
		tmp=tmp->next;
	}
	return(0);
}

int verif_arg_env(char *str)
{
	int i;

	i = -1;
	if(str[0] == '=' || ft_isdigit(str[0]))
		return(1);
	while(str[++i])
		if(!ft_isalpha(str[i]) && str[i] != '_' && str[i] != '=' && !ft_isdigit(str[i]))
			return(1);
	return(0);
}

void	fonction_export(t_shell *shell)
{
	int			i;
	char		*arg;
	t_list_cmd	*tmp;
	t_list_env	*tmp_env;

	printf("act_export\n");
	i = 1;
	tmp_env = shell->env;
	tmp = shell->list_cmd;

	if (!tmp->arg[i])
	{
		while (tmp_env)
		{
			if (tmp_env->content)
				printf("declare -x %s=\"%s\"\n", tmp_env->name, tmp_env->content);
			else
				printf("declare -x %s\n", tmp_env->name);
			tmp_env = tmp_env->next;
		}
	}
	while (tmp->arg[i])
	{
		arg = tmp->arg[i];
		printf("arg=%s\n",arg);
		if(verif_arg_env(arg) != 0)
		{

			shell->ret_value = 1;
			printf("export: '%s' : not a valid identifier\n", arg);
		}
		else if (strchr(arg, '='))
		{
			delete_env(shell, ft_substr(arg, 0, ft_strchr(arg, '=') - arg));
			ft_add_back_env(&shell->env, ft_lstnew_env(ft_strchr(arg, '=') + 1 \
			, ft_substr(arg, 0, ft_strchr(arg, '=') - arg)));
		}
		else if(exist_env(shell, arg) == 0)
			ft_add_back_env(&shell->env, ft_lstnew_env(NULL, arg));
		i++;
	}
}

void	fonction_unset(t_shell *shell)
{
	int	i;

	(void)shell;
	printf("act_unset\n");
	i = -1;
	if (!shell->list_cmd->arg[1])
		return ;
	if (verif_arg_env(shell->list_cmd->arg[1]) != 0)
	{
		shell->ret_value = 1;
		printf("unset: '%s' : not a valid identifier\n", shell->list_cmd->arg[1]);
	}
	while (shell->list_cmd->arg[++i])
		delete_env(shell, shell->list_cmd->arg[i]);
}

void	fonction_pwd(t_shell *shell)
{
	char	*buf;

	(void)shell;
	printf("act_pwd\n");
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
}

void	fonction_echo(t_shell *shell)
{
	int	i;

	(void)shell;
	printf("act_echo\n");
	i = 1;
	if (shell->list_cmd->arg[i])
	{
		i += (ft_strncmp(shell->list_cmd->arg[i], "-n", 3) == 0);
		while (shell->list_cmd->arg[i])
		{
			printf("%s", shell->list_cmd->arg[i]);
			i++;
			if (shell->list_cmd->arg[i])
				printf(" ");
		}
		if (ft_strncmp(shell->list_cmd->arg[1], "-n", 3))
			printf("\n");
	}
	else
		printf("\n");
}

void	modif_env(t_shell *shell, char *name, char *new_content)
{
	t_list_env	*tmp;

	tmp = shell->env;
	while (tmp && strncmp(tmp->name, name, ft_strlen(name)))
		tmp = tmp->next;
	if (tmp)
	{
		tmp->content = ft_calloc(ft_strlen(new_content), 1);
		tmp->content = new_content;
	}
}

void	fonction_cd(t_shell *shell)
{
	char	**tmp;
	char	*old;
	int		ret;

	printf("act_cd\n");
	old = getcwd(NULL, 0);
	tmp = shell->list_cmd->arg;
	(void)shell;
	if (!tmp[1] || ft_strncmp(tmp[1], "~", 2) == 0)
		ret = chdir(ft_get_env(shell, "HOME"));
	else
		ret = chdir(tmp[1]);
	modif_env(shell, "OLDPWD", old);
	modif_env(shell, "PWD", getcwd(NULL, 0));
	tmp = shell->list_cmd->arg;
	if (!tmp[1])
	{
		tmp[1] = ft_strdup(getenv("HOME"));
		tmp[2] = 0;
	}
	else if (tmp[1][0] == '~')
		tmp[1] = ft_strjoin(getenv("HOME"), tmp[1] + 1);
	if (ret == -1)
	{
		
		shell->ret_value = 1;	
		printf(": cd: %s: No such file or directory\n", tmp[1]);
	}
}

void	fonction_execve(t_shell *shell)
{
	t_list_cmd	*tmp;

	printf("act_execve\n");
	if(shell->list_cmd->arg[0]== NULL)
		exit (1);
	if (shell->list_cmd->cmd == NULL && !is_builtin(shell->list_cmd->arg[0]))
	{
		if (ft_check_exist_path(shell) == -1)
			printf("%s: command not found\n", shell->list_cmd->arg[0]);
	}
	init_dup_file(shell);	
	tmp = shell->list_cmd;
	if (execve(tmp->cmd, tmp->arg, shell->tab_env) == -1)
		exit(1);
}
