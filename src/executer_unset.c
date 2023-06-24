/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:46:30 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:46:33 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_not_alphanum(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if ((str[i] == '+' || str[i] == '='))
				return (0);
			i++;
		}
	}
	return (1);
}

t_env	*my_unset(t_commnd *cmd, t_env **env)
{
	t_env	*current;
	t_utils	utils;
	int		i;

	i = 1;
	current = *env;
	while (cmd->cmd[i])
	{
		unset_helper(cmd, i);
		unset_helper2(cmd, i, env, utils);
		if (utils.flag == 0)
			return (0);
		i++;
	}
	return (*env);
}
