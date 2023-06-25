/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ftutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:41:20 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 02:41:21 by haouadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_str(char *string, long long int nb, int size)
{
	if (nb == 0)
		string[0] = '0';
	else if (nb < 0)
	{
		nb *= -1;
		string[0] = '-';
	}
	size--;
	while (size >= 0 && nb != 0)
	{
		string[size] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
}

int	string_size(long long int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i ++;
	}
	if (nb != 0)
	{
		while (nb != 0)
		{
			nb = nb / 10;
			i++;
		}
	}
	else
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*string;
	long long int	nb;
	int				size;

	nb = n;
	size = string_size(nb);
	string = (char *)malloc(sizeof(char) * size + 1);
	if (!string)
		return (NULL);
	put_str(string, nb, size);
	string[size] = '\0';
	return (string);
}

int	ft_spchar_len(char *str, char d1, char d2)
{
	int	len;

	len = 0;
	if (!d1)
		d1 = d2;
	else if (!d2)
		d2 = d1;
	while (str[len] && (str[len] == d1 || str[len] == d2))
		len++;
	return (len);
}

int	ft_arg_len(char *str)
{
	int		len;
	char	q;

	len = -1;
	while (str[++len])
	{
		if (str[len] == '"' || str[len] == '\'')
		{
			q = str[len++];
			while (str[len] && str[len] != q)
				len++;
		}
		if (str[len] == ' ' || str[len] == '|' || str[len] == '>'
			|| str[len] == '<' || !str[len])
			break ;
	}
	return (len);
}
