/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:33:56 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:33:59 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_key(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*ft_sersh_val(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	check_for_signe(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_env	*sort_export(t_env *lst)
{
	char	*swap;
	t_env	*current;

	current = lst;
	if (ft_lstsize(current) < 1)
		return (lst);
	while (current->next != NULL)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			swap = current->key;
			current->key = current->next->key;
			current->next->key = swap;
			swap = current->value;
			current->value = current->next->value;
			current->next->value = swap;
			current = lst;
		}
		else
			current = current->next;
	}
	current = lst;
	return (lst);
}

t_env	*my_export(t_commnd *cmd, t_env *lst, t_utils *utils)
{
	t_env	*current;
	
	current = lst;
	utils->i = 0;
	print_export(cmd, current);
	while (cmd->cmd[++utils->i])
	{
		if (errors_export(cmd, utils->c, utils->i) == 0)
			continue ;
		utils->c = check_for_signe(cmd->cmd[utils->i], '=');
		if (utils->c != -1)
		{
			if (cmd->cmd[utils->i][utils->c - 1] != '+')
				export_helper(cmd, lst, utils->i);
			else
				export_plus_case(cmd, utils, lst, utils->i);
		}
		else
			if (ft_search_key(lst, cmd->cmd[utils->i]))
				ft_lstadd_back(&lst, ft_lstnew(cmd->cmd[utils->i], NULL));
	}
	g_global.exit_code = 0;
	return (lst);
}
