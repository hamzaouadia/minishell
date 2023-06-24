/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:33:07 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:33:10 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_commnd *cmd, t_env *current)
{
    char    *str_key;
    char    *str_;
    char    *str_var;
	if (ft_strcmp(cmd->cmd[0], "export") == 0 && !cmd->cmd[1])
	{
		sort_export(current);
		while (current)
		{
            str_key = ft_strjoin(current->key, "=");
            str_ = ft_strjoin(current->value, "\"");
            str_var = ft_strjoin(str_key, str_);
			if (current->value)
				printf("declare -x %s\n", str_var);
			else
				printf("declare -x %s\n", current->key);
            free (str_);
            free (str_key);
            free (str_var);
			current = current->next;
		}
	}
	g_global.exit_code = 0;
}

int	errors_export(t_commnd *cmd, int c, int i)
{
	c = check_for_signe(cmd->cmd[i], '+');
	if (c != -1 && cmd->cmd[i][c + 1] != '=')
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd->cmd[i]);
		g_global.exit_code = 1;
		return (0);
	}
	if ((cmd->cmd[i][0] != '_' && (ft_isalpha(cmd->cmd[i][0]) == 1))
		|| ft_cheeck(cmd->cmd[i]) == -1)
	{
		printf("bash: export: `%s': not a valid identifier\n", cmd->cmd[i]);
		g_global.exit_code = 0;
		return (0);
	}
	return (1);
}

char	*ft_sersh_key(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void	export_plus_case(t_commnd *cmd, t_utils *utils, t_env *lst, int i)
{
	utils->str = ft_substr(cmd->cmd[i], 0, ft_len(cmd->cmd[i], '+'));
	utils->current = lst;
	if (ft_sersh_key(utils->current, utils->str))
	{
		while (utils->current)
		{
			if (ft_strcmp(utils->current->key, utils->str) == 0)
			{
				if (utils->current->value)
					utils->current->value = ft_strjoin(utils->current->value,
							ft_substr(cmd->cmd[i], ft_len(cmd->cmd[i], '=') + 1,
								ft_len(cmd->cmd[i], '\0')));
				else
					utils->current->value = ft_substr(cmd->cmd[i],
							ft_len(cmd->cmd[i],
								'=') + 1, ft_len(cmd->cmd[i], '\0'));
			}
			utils->current = utils->current->next;
		}
	}
	else
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(cmd->cmd[i], 0,
					ft_len(cmd->cmd[i], '+')), ft_substr(cmd->cmd[i],
					ft_len(cmd->cmd[i], '=') + 1, ft_len(cmd->cmd[i], '\0'))));
	g_global.exit_code = 0;
}

void	export_helper(t_commnd *cmd, t_env *lst, int i)
{
	t_env	*current;

	current = lst;
	if (ft_search_key(lst, ft_substr(cmd->cmd[i], 0, ft_len(cmd->cmd[i],
					'='))) == 0)
	{
		while (current)
		{
			if (ft_strcmp(current->key, ft_substr(cmd->cmd[i], 0,
						ft_len(cmd->cmd[i], '='))) == 0)
				current->value = ft_substr(cmd->cmd[i], ft_len(cmd->cmd[i], '=')
						+ 1, ft_len(cmd->cmd[i], '\0'));
			current = current->next;
		}
		current = lst;
	}
	else
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(cmd->cmd[i], 0,
					ft_len(cmd->cmd[i], '=')), ft_substr(cmd->cmd[i],
					ft_len(cmd->cmd[i], '=') + 1, ft_len(cmd->cmd[i], '\0'))));
	}
	g_global.exit_code = 0;
}
