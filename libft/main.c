int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_temp[i] != s2_temp[i] || s1_temp[i] == '\0')
			return (s1_temp[i] - s2_temp[i]);
		i++;
	}
	return (0);
}

int main()
{
	ft_strncmp("oui", "comment", 5);
}
