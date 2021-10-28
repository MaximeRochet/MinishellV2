#include "../includes/minishell.h"

/*
void    ft_fill_redir(t_shell *shell)
{
    t_list_cmd *list;
    int i;
    int y;
    char *str;
    char *tmp_redi;

    list = shell->list_cmd;
    i = 0;
    while (list)
    {
        while (list->arg[i])
        {
            y = 0;
            str = list->arg[i];
            while (str[y])
            {
                printf("list->arg[%d] = |%s|\n", i, list->arg[i]);
                if ((str[y] == '>' || str[y] == '<') && ft_strlen(list->arg[i]) == 1)
                {
                        tmp_redi = strdup(ft_strjoin(list->arg[i], list->arg[i + 1]));
                }
                else if ((str[y] == '>' || str[y] == '<') && ft_strlen(list->arg[i]) != 1 && ((str[y +1 ] != '>' && str[y + 1] != '<')))
                    tmp_redi = strdup(list->arg[i]);
                else if ((str[y] == '>' || str[y] == '<') && ft_strlen(list->arg[i]) == 2 && ((str[y +1 ] == '>' || str[y + 1] == '<')))
                {

                    printf("coucou\n");
                    tmp_redi = strdup(ft_strjoin(list->arg[i], list->arg[i + 1]));
                }
                else if ((str[y] == '>' || str[y] == '<') && ft_strlen(list->arg[i]) != 1 && ((str[y +1 ] == '>' || str[y + 1] == '<')))
                    tmp_redi = strdup(ft_strjoin(list->arg[i], list->arg[i + 1]));
                y++;
            }
            i++;
        }
        list = list->next;
    }
    dprintf(1, "tmp_redi = |%s|\n", tmp_redi);
    return ;
    
}
*/
