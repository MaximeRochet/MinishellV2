#include "../includes/minishell.h"

char *add_char(char *str, int space, char c)
{
	char *tmp;
	int i;
	
	i = 0;
	tmp = str;
	tmp = malloc(sizeof(char) * ft_strlen(str)+2);
	while(i < space)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	while(i != (int)ft_strlen(str)+1)
	{
		tmp[i+1] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return(tmp);
}	

char *find_redir(char *str)
{
	int	i;
	char	quote;

	i = -1;
	quote = '\200';
	while(str[++i])
	{
		if((str[i] == '\"' || str[i] == '\'') && quote == '\200')
			quote = str[i];
		else if(str[i] == quote)
			quote = '\200';
		if((str[i] == '<' || str[i] == '>') && i && quote == '\200')
		{
			if(str[i-1] != ' ' && str[i-1] != str[i])
				str = add_char(str, i, ' ');
		}
		if((str[i] == '<' || str[i] == '>') && quote == '\200')
		{
			if(str[i+1] != ' ' && str[i] != str[i+1])
				str = add_char(str, i+1, ' ');
		}
	}	
	return(str);
}
