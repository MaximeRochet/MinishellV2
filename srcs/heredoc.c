/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasse <cmasse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:02:59 by cmasse            #+#    #+#             */
/*   Updated: 2021/11/09 18:04:18 by cmasse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_size_secur(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_join_doc(char *s1, char *s2)
{
	size_t	len;
	char	*str;

	len = ft_size_secur(s1) + ft_size_secur(s2);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	ft_memcpy((void *)str, s1, ft_size_secur(s1));
	ft_strlcat((char *)str, (char *)s2, len + 1);
	free(s1);
	return (str);
}

int	compare(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2 && n--)
	{
		if (*s1 != *s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}

void	here_doc(char *s)
{
	char	*line;
	char	buf[2];
	int		fd;

	fd = open(".here_doc", O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IRWXU);
	line = NULL;
	while (compare(s, line, ft_size_secur(line) - 1))
	{
		write(1, "> ", 2);
		if (line)
			write(fd, line, ft_size_secur(line));
		free(line);
		line = NULL;
		buf[0] = '\0';
		while (buf[0] != '\n')
		{
			read(0, buf, 1);
			buf[1] = '\0';
			line = ft_join_doc(line, buf);
		}
	}
	free(line);
	close(fd);
}
