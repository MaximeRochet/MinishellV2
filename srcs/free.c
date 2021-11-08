
#include "../includes/minishell.h"

void    ft_free(char **s)
{
    int i;

    i = 0;
    if(s)
    {
        while(s[i])
            free(s[i++]);
    }
}