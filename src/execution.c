/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:13:01 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/24 16:13:06 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count >= SIZE_MAX / size)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

static	int	count(char c, char *s)
{
	int	i;
	int	m;

	m = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			m++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (m);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static char	*allocation(char *s, int n)
{
	char	*a;
	int		i;

	a = malloc(sizeof(char) * n + 1);
	if (!a)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**a;

	i = 0;
	k = 0;
	a = ft_calloc(count(c, s) + 1, sizeof(char *));
	if (!a)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			a[k] = allocation(s + j, i - j);
			if (!a[k++])
				return (ft_free(a));
		}
	}
	return (a);
}
