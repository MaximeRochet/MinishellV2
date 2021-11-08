#include "../includes/minishell.h"

int ft_exit(t_shell *shell)
{
	char **tab;
	int i;

	i = 0;
	tab = ft_split(shell->str_cmd, ' ');
	if(tab[1])
	{
		printf("exit\n");	
		while(ft_isalpha(tab[1][i]))
			i++;
		if (!ft_isdigit(tab[1][i]))
			printf("exit: %s: numeric argument required\n", tab[1]);
		return (0);
	}
	printf("exit\n");
	return(0);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	int		i;

	(void)ac;
	(void)av;
	shell = ft_calloc(sizeof(t_shell), 1);
	//ft_format_struct(shell);
	init_env(env, shell);
	//shell.str_cmd = (char *)calloc(sizeof(char),1);
	//if(!shell.str_cmd)
	//{
	//   printf("Malloc failure");
	//  return (0);
	//}
	i = 0;
	while (!shell->str_cmd || ft_strncmp(shell->str_cmd, "exit", 4))
	{
		shell->prompt = recup_prompt();
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->str_cmd = readline(shell->prompt);
		if (!shell->str_cmd)
			break ;
		if (shell->str_cmd && ft_strlen(shell->str_cmd) > 0 && ft_strncmp(shell->str_cmd, "exit", 4))
		{	
			add_history(shell->str_cmd);
			if (parsing(shell) == 0 && shell->quit == 0)
			{
				
				shell->ret_value = i;
				execution(shell);
				i = shell->ret_value;
				shell->ret_value = 0;
			}
			shell->list_cmd = NULL;
			//ft_format_struct(shell);
			//free(shell.str_cmd);
		}
	}
	ft_exit(shell);
	free(shell->str_cmd);
	return (0);
}
