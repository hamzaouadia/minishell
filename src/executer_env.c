/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:25:48 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/24 16:01:22 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_my_env_cond(t_commnd *cmd, t_env *lst, int x)
{
	t_env	*current;

	current = lst;
	if (lst == NULL)
	{
		printf("env : No such file or directory\n");
		g_global.exit_code = 127;
		lst = current;
		return (1);
	}
	if (x >= 2)
	{
		printf("env: %s: No such file or directory\n",
			cmd->cmd[1]);
		g_global.exit_code = 127;
		return (1);
	}
	return (0);
}

void	ft_print_env(t_env *current)
{
	char	*str_key;
	char	*str_var;

	while (current)
	{
		if (current->value)
		{
			str_key = ft_strjoin(current->key, "=");
			str_var = ft_strjoin(str_key, current->value);
			printf("%s\n", str_var);
			free(str_key);
			free(str_var);
		}
		current = current->next;
	}
}

void	my_env(t_commnd *cmd, t_env *lst)
{
	int		x;
	t_env	*current;

	current = lst;
	x = count_args(cmd->cmd);
	while (lst)
	{
		if (ft_strcmp(lst->key, "PATH") == 0)
			break ;
		lst = lst->next;
	}
	if (ft_my_env_cond(cmd, lst, x))
		return ;
	ft_print_env(current);
	g_global.exit_code = 0;
}
