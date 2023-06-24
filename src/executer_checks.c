/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:23:12 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:23:14 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (0);
	}
	return (1);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (0);
	}
	return (1);
}

int	ft_isalnumm(char c)
{
	if (!(ft_isalpha(c) && ft_isdigit(c))
		|| c == '_' || c == '=' || c == '+')
		return (0);
	return (1);
}

int	is_spec_carac(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
		return (0);
	return (1);
}

int	ft_cheeck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalnumm(str[i]))
			return (-1);
		i++;
	}
	return (0);
}
