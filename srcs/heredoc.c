#include "../includes/minishell.h"

void    here_doc(char *s)
{
	char	*line;
	char 	*tmp;
	char 	buf[2];
	int 	fd;

	fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IRWXU);
	line = NULL;
	while (ft_strncmp(s, line, ft_strlen(line) - 1))
	{
		write(1, "> ", 2);
		if (line)
			write(fd, line, strlen(line));
		free(line);
		line = NULL;
		buf[0] = '\0';
		while (buf[0] != '\n')
		{
			read(0, buf, 1);
			buf[1] = '\0';
			tmp = line;
			line = ft_strjoin(line, buf);
			free(tmp);
		}
	}
	free(line);
	close(fd);
}
