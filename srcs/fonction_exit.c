
#include "../includes/minishell.h"

void	fonction_env_exit(t_shell *shell)
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
    exit(0);
}

void	fonction_export_exit(t_shell *shell)
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
		if(verif_arg_env(arg) != 'a')
		{
            printf("%c caractere invalide\n", verif_arg_env(arg));
            exit(1);
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
    exit(0);
}

void	fonction_unset_exit(t_shell *shell)
{
	int	i;

	(void)shell;
	printf("act_unset\n");
	i = -1;
	if (!shell->list_cmd->arg[1])
		exit(0);
	else if(verif_arg_env(shell->list_cmd->arg[0]) != 'a')
	{
        printf("%c caractere invalide\n", verif_arg_env(shell->list_cmd->arg[0]));
        exit (1);
    }
	while (shell->list_cmd->arg[++i])
		delete_env(shell, shell->list_cmd->arg[i]);
    exit(0);
}

void	fonction_pwd_exit(t_shell *shell)
{
	char	*buf;

	(void)shell;
	printf("act_pwd\n");
	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
    exit(0);
}

void	fonction_echo_exit(t_shell *shell)
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
    exit(0);
}

void	fonction_cd_exit(t_shell *shell)
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
        printf(": cd: %s: No such file or directory\n", tmp[1]);
        exit(1);
    }
    exit(0);
}
