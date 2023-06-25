/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:41:56 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 11:29:43 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_red	*ft_lstnew_red(void *rd)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		exit (0);
	red->rd = rd;
	red->fl = rd;
	red->next = NULL;
	return (red);
}

t_argument	*ft_lstnew_arg(void *arg)
{
	t_argument	*argument;

	argument = malloc(sizeof(t_argument));
	if (!argument)
		exit (0);
	argument->arg = arg;
	argument->next = NULL;
	return (argument);
}

t_command	*ft_cmndnew(char *str)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		exit (0);
	command->cmnd = str;
	command->pipe = '\0';
	command->next = NULL;
	command->red = ft_lstnew_red(NULL);
	command->argument = ft_lstnew_arg(NULL);
	return (command);
}

t_all	*ft_all_init(char **envp)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->heredocc = NULL;
	all->fds = malloc(sizeof(t_fds));
	all->utils = malloc(sizeof(t_utils));
	all->lst = NULL;
	copy_env(envp, &all->lst);
	g_global.env = all->lst;
	return (all);
}

t_commnd	*ft_transfer_cmd(t_command *command)
{
	t_commnd	*cmd;
	t_commnd	*cmd_head;
	int			i;

	cmd = ft_new_cmd();
	cmd_head = cmd;
	while (command->next)
	{
		i = ft_transfer_command(command, i, cmd);
		ft_transfer_arg(command->argument, command->red, cmd, i);
		command = command->next;
		cmd->next = ft_new_cmd();
		cmd = cmd->next;
	}
	cmd = cmd_head;
	return (cmd);
}
