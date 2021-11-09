/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:50:58 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 16:03:32 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <pwd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_list_env
{
	char				*content;
	char				*name;
	struct s_list_env	*next;

}						t_list_env;

typedef struct s_list_cmd
{
	char				*cmd;
	char				**arg;
	int					pipe;
	int					redir_in;
	int					redir_out;
	struct s_list_cmd	*next;
}						t_list_cmd;

typedef struct s_shell
{
	char		*str_cmd;
	char		*prompt;
	int			size_list_cmd;
	int			**pipes;
	int			*pids;
	int			quit;
	int			ret_value;
	char		**tab_env;	

	t_list_cmd	*list_cmd;
	t_list_env	*env;
}				t_shell;

typedef struct s_fonc
{
	char	*name;
	void	(*fct)(t_shell *shell);
}			t_fonc;

// LIST
void		ft_add_back_cmd(t_list_cmd **n, t_list_cmd *new);

//void	ft_add_front_cmd(t_list_cmd **n, t_list_cmd *new);
void		ft_add_back_env(t_list_env **alst, t_list_env *new);
t_list_cmd	*ft_new_cmd(char **arg);
t_list_env	*ft_lstnew_env(void *content, void *name);

// UTILS 
//void	ft_get_path(t_shell *shell, char *c);
char		*ft_strstr(char *str, char *to_find);
void		print_list_cmd(t_list_cmd *list);
void		print_shell(t_shell *shell);
int			char_is_in(char *str, char c);
int			ft_index_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_strcat(char *dst, const char *src);

void		print_env(t_list_env *lst);
char		*ft_get_env(t_shell *shell, char *name);
char		*find_redir(char *str);
char		*add_char(char *str, int space, char c);

// PARSING
// PARSING_INIT
void		init_env(char **env, t_shell *shell);
void		ft_format_struct(t_shell *shell);
int			parsing(t_shell *shell);
int			ft_valide_quote_str(t_shell *shell);

// 	PARSING_VAR
int			ft_check_variable(t_shell *shell, int i);
void		ft_replace_var(t_shell *shell, int i, int y);
char		*ft_delete_var(int start, int end, t_shell *shell);
char		*ft_paste_name_var(int start, char *var, t_shell *shell, int i);

// PARSING_PIPE
char		*ft_replace_pipe_str(char *str, char c);
char		**ft_split_pipe_str(char *str);
void		ft_split_arg_str(t_shell *shell, char **str_split);

// PARSING_CMD
void		ft_remove_quote_cmd(t_shell *shell);
void		ft_path_cmd(t_shell *shell);
int			ft_check_exist_path(t_shell *shell);

// PARSING_REDIRECTION
void		ft_fill_redir(t_shell *shell);

//FONCTION PRINCIPALES
char		*recup_prompt(void);
char		*shearch_in_env(t_list_env *env, char *name);
void		modif_env(t_shell *shell, char *name, char *new_content);
int			verif_arg_env(char *str);
void		delete_env(t_shell *shell, char *name);
int			exist_env(t_shell *shell, char *arg);

//EXECUTION
int			find_function(t_shell *shell);
void		find_function_exit(t_shell *shell);
int			is_builtin(char *s);
void		ft_replace_ret_values(t_shell *shell);
int			init_dup_file(t_shell *shell);

//EXECUTION_DEUX 
void		child_process_start(t_shell *shell, int i);
void		child_process_middle(t_shell *shell, int i);
void		child_process_end(t_shell *shell, int i);
void		child_process(t_shell *shell, int i);

//EXECUTION_TROIS
void		pipex(t_shell *shell);
void		pipex_next(t_shell *shell, int i);
int			execution(t_shell *shell);

//BUILT-IN
void		fonction_cd(t_shell *shell);
void		fonction_echo(t_shell *shell);
void		fonction_env(t_shell *shell);
void		fonction_export(t_shell *shell);
void		fonction_unset(t_shell *shell);
void		fonction_pwd(t_shell *shell);
void		fonction_execve(t_shell *shell);
void		ft_ret_values(t_shell *shell, int pid);
void		ft_signal_handler(int sig);

//FONCTION_EXIT
void		fonction_env_exit(t_shell *shell);
void		fonction_export_exit(t_shell *shell);
void		fonction_unset_exit(t_shell *shell);
void		fonction_pwd_exit(t_shell *shell);
void		fonction_echo_exit(t_shell *shell);
void		fonction_cd_exit(t_shell *shell);

//FREE
void		ft_free(char **s);
void		free_shell(t_shell *shell);

//HEREDOC
void		here_doc(char *s);
#endif	
