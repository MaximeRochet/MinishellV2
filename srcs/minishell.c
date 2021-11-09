/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:01:23 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 19:19:01 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_shell *shell)
{
	char	**tab;
	int		i;

	i = 0;
	if (!shell->str_cmd)
	{
		printf("exit\n");
		return (0);
	}
	tab = ft_split(shell->str_cmd, ' ');
	free_shell(shell);
	printf("exit\n");
	if (tab[1])
	{
		while (ft_isalpha(tab[1][i]))
			i++;
		if (!ft_isdigit(tab[1][i]))
			printf("exit: %s: numeric argument required\n", tab[1]);
		else
			return (ft_atoi(tab[1]) % 256);
		return (255);
	}
	return (0);
}

void	main_next(t_shell *shell, int *ac)
{
	shell->ret_value = *ac;
	execution(shell);
	*ac = shell->ret_value;
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)av;
	shell = ft_calloc(sizeof(t_shell), 1);
	init_env(env, shell);
	ac = 0;
	while (!shell->str_cmd || ft_strncmp(shell->str_cmd, "exit", 4))
	{
		shell->prompt = recup_prompt();
		signal(SIGINT, ft_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		shell->str_cmd = readline(shell->prompt);
		if (!shell->str_cmd)
			break ;
		if (shell->str_cmd && ft_strlen(shell->str_cmd) > 0 \
		&& ft_strncmp(shell->str_cmd, "exit", 4))
		{	
			add_history(shell->str_cmd);
			if (parsing(shell) == 0 && shell->quit == 0)
				main_next(shell, &ac);
			shell->list_cmd = NULL;
		}
	}
	exit(ft_exit(shell));
}
