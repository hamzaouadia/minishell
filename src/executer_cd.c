/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:22:20 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:22:23 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mise_ajour_pwd_before(t_env *lst)
{
	t_env	*current;
	char	*old_pwd;

	current = lst;
	while (current)
	{
		if (ft_strncmp(current->key, "OLDPWD", 6) == 0)
		{
			old_pwd = ft_strdup(current->value);
		}
		current = current->next;
	}
	return (old_pwd);
}

void	mise_ajour_pwd2_after(t_env **lst, char *new, int c)
{
	t_env	*current;

	current = *lst;
	while (current)
	{
		if (c == 1 && ft_strncmp(current->key, "PWD", 3) == 0)
		{
			current->value = new;
		}
		else if (c == 2 && ft_strncmp(current->key, "OLDPWD", 6) == 0)
		{
			current->value = new;
		}
		current = current->next;
	}
}

char	*home(t_env *lst)
{
	t_env	*current;
	char	*home;

	home = NULL;
	g_global.env = lst;
	current = g_global.env;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 4) == 0)
		{
			home = ft_strdup(current->value);
		}
		current = current->next;
	}
	return (home);
}

void	my_cd(t_commnd *cmd, t_env	*my_list, t_utils *utils)
{
	char	*test;

	test = NULL;
	utils->old = my_pwd(1, my_list);
	if ((ft_strcmp(cmd->cmd[0], "cd") == 0 && !cmd->cmd[1])
		|| ((ft_strcmp(cmd->cmd[0], "cd") == 0) && ft_strcmp(cmd->cmd[1],
				"~") == 0))
	{
		utils->my_home = home(my_list);
		if (chdir(utils->my_home) == -1)
			print_errors_cd(1);
		g_global.exit_code = 0;
	}
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0 && ft_strcmp(cmd->cmd[1],
			"-") == 0)
		cd_helper2(my_list, utils);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0 && ft_strcmp(cmd->cmd[1],
			".") == 0)
		cd_helper1(test);
	else if (chdir(cmd->cmd[1]) == -1)
		(printf("minishell: cd: %s: No such file or directory\n",
				cmd->cmd[1]), g_global.exit_code = 1);
	utils->new = my_pwd2(1, my_list);
	mise_ajour_pwd2_after(&my_list, utils->new, 1);
	mise_ajour_pwd2_after(&my_list, utils->old, 2);
}
