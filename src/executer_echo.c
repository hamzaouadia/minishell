/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:25:12 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 15:32:44 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args_with_index(char **cmd, int index)
{
	while (cmd[index] != NULL)
	{
		printf("%s", cmd[index]);
		if (cmd[index + 1] != NULL)
			printf(" ");
		index++;
	}
	if (check_n(cmd[1]))
		printf("\n");
}

int	check_n(char *str)
{
	int	i;
	int	found_n;

	i = 1;
	found_n = 0;
	if (!str)
		return (0);
	while (str[0] && str[i])
	{
		if (str[i] == 'n')
			found_n ++;
		else
			break ;
		i++;
	}
	if (found_n && found_n == ft_strlen(str) - 1)
		return (0);
	return (1);
}

void	check_args_option_n(t_commnd *cmd, int i)
{
	if (!check_n(cmd->cmd[i]))
	{
		while (cmd->cmd[i] && !check_n(cmd->cmd[i]))
			i++;
		if (!cmd->cmd[i])
			return ;
		print_args_with_index(cmd->cmd, i);
	}
	else
		print_args_with_index(cmd->cmd, i);
}

void	my_echo(t_commnd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->cmd[i])
	{
		printf("\n");
		return ;
	}
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '-')
		{
			check_args_option_n(cmd, i);
			break ;
		}
		else
		{
			print_args_with_index(cmd->cmd, i);
			break ;
		}
		i++;
	}
	g_global.exit_code = 0;
}
