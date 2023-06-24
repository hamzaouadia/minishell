/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_unset_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:45:17 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:46:05 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_helper(t_commnd *cmd, int i)
{
	if ((cmd->cmd[i][0] != '_' && (ft_isalpha(cmd->cmd[i][0]) == 1))
		|| ft_cheeck(cmd->cmd[i]) == -1 || !find_not_alphanum(cmd->cmd[i]))
		printf("bash: unset: `%s': not a valid identifier\n", cmd->cmd[i]);
}

void	unset_helper2(t_commnd *cmd, int i, t_env **env, t_utils utils)
{
	t_env	*previous;
	t_env	*current;

	current = *env;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(cmd->cmd[i], current->key) == 0)
		{
			if (previous == NULL)
			{
				*env = current->next;
				(free(current->key), free(current->value));
			}
			else
			{
				previous->next = current->next;
				(free(current->key), free(current->value));
				utils.flag = 1;
			}
		}
		previous = current;
		current = current->next;
	}
}
