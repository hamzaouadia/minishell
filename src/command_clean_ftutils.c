/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clean_ftutils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:38:33 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 02:38:35 by haouadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes_len(char *str)
{
	int		i;
	int		quotes;
	char	q;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quotes++;
			q = str[i++];
			while (str[i] != q && str[i])
				i++;
		}
		i++;
	}
	return (quotes);
}

int	ft_quotes_syntax(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			q = str[i++];
			while (str[i] != q && str[i])
				i++;
			if (str[i] == '\0')
			{
				printf("-bash: syntax error\n");
				g_global.exit_code = 258;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
