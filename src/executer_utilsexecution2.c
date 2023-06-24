#include "minishell.h"

char	*ft_strnstr(char *src, char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(to_find) > ft_strlen(src))
		return (NULL);
	else if (to_find[j] == '\0')
		return ((char *)src);
	else if (n == 0)
		return (NULL);
	while (src[i] && i < n)
	{
		j = 0;
		while (src[i + j] == to_find[j] && i + j < n)
		{
			if (to_find[j + 1] == '\0')
				return ((char *)&src[i]);
		j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	char	*b;
	int		i;

	i = 0;
	b = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!b)
		return (0);
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}

int	ft_atoi(char *str)
{
	int						i;
	int						signe;
	unsigned long long		nmbr;

	i = 0;
	signe = 1;
	nmbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nmbr = nmbr * 10 + (str[i] - 48);
		i++;
	}
	if (nmbr >= 9223372036854775807 && signe > 0)
		return (-1);
	else if (nmbr > 9223372036854775807 && signe < 0)
		return (0);
	return (nmbr * signe);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && s2)
		return (s2[i]);
	if (s1 && !s2)
		return (s1[i]);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{	
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t	ft_strlen2(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}
// void	leaks_removal(t_leaks **leaks, void *ptr)
// {
// 	t_leaks	*garbage;

// 	garbage = malloc(sizeof(t_leaks));
// 	garbage->leak = ptr;
// 	garbage->next = *(leaks);
// 	*leaks = garbage;
// }