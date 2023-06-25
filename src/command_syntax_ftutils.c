/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_syntax_ftutils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:39:00 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 02:39:01 by haouadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_white_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	ft_file_condition(char *str, int i, t_command *command)
{
	int	len;
	int	j;

	j = 0;
	if (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
	{
		i = ft_white_spaces(str, i);
		len = ft_arg_len(str + i);
		command->red->fl = calloc((len + 1), sizeof(char));
		while (len > j)
			command->red->fl[j++] = str[i++];
		command->red->fl[j] = '\0';
		i = ft_white_spaces(str, i);
	}
	else
	{
		printf("-bash: syntax error near unexpected token\n");
		g_global.exit_code = 258;
		return (-1);
	}
	return (i);
}

int	ft_cmnd_after_red(char *str, int i, t_command *command)
{
	int	len;
	int	j;

	j = 0;
	if (str[i] && str[i] != '<' && str[i] != '>'
		&& command->cmnd == NULL && str[i] != '|')
	{
		i = ft_white_spaces(str, i);
		j = 0;
		len = ft_arg_len(str + i);
		command->cmnd = calloc((len + 1), sizeof(char));
		while (len > j)
			command->cmnd[j++] = str[i++];
		i = ft_white_spaces(str, i);
	}
	return (i);
}
