/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:32:56 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:32:59 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	my_exit(t_commnd *cmd)
{
	int	i;
	int	x;

	x = count_args(cmd->cmd);
	if (x == 1)
		utils_exit(3);
	else
	{
		i = 0;
		while (cmd->cmd[1][i])
		{
			if (!(cmd->cmd[1][i] >= '0' && cmd->cmd[1][i] <= '9'))
			{
				utils_exit(0);
			}	
			i++;
		}
		if (x == 2)
			(printf("exit\n"), exit(ft_atoi(cmd->cmd[1])));
		else if (x > 2)
			utils_exit(1);
		else
			utils_exit(2);
	}
	return (0);
}
