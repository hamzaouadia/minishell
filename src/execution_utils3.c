/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:13:23 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/24 16:13:25 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;

	i = 0;
	if (start >= ft_strlen2(s))
	{
		a = malloc(sizeof(char));
		if (!a)
			return (0);
		a[0] = '\0';
		return (a);
	}
	if (len > ft_strlen2(s))
		a = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		a = malloc (sizeof(char) * len + 1);
	if (!a)
		return (0);
	while (s[start + i] && i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*a ;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	a = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!a)
		return (0);
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j])
		a[i++] = s2[j++];
	a[i] = '\0';
	return (a);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*b;

	b = (char *)s;
	i = 0;
	while (b[i])
	{
		if (b[i] == (char)c)
			return ((char *) &s[i]);
		i++;
	}
	if (b[i] == (char)c)
		return ((char *) &s[i]);
	return (0);
}

int	ft_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	return (1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (a);
}
