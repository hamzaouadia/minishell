/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:42:33 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 11:33:39 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_transfer_arg(t_argument *argument, t_red *red, t_commnd *cmd, int i)
{
	while (argument->arg)
	{
		cmd->cmd[i++] = strdup(argument->arg);
		free(argument->arg);
		argument = argument->next;
	}
	cmd->cmd[i] = NULL;
	i = 0;
	while (red->rd)
	{
		cmd->file[i++] = strdup(red->rd);
		cmd->file[i++] = strdup(red->fl);
		free(red->rd);
		free(red->fl);
		red = red->next;
	}
	cmd->file[i] = NULL;
}

int	ft_transfer_command(t_command *command, int i, t_commnd *cmd)
{
	int	fl_len;
	int	arg_len;

	fl_len = 0;
	arg_len = 0;
	i = 0;
	arg_len = ft_count_arg(command->argument);
	if (command->cmnd)
		arg_len++;
	fl_len = ft_count_file(command->red);
	cmd->cmd = malloc(sizeof(char *) * (arg_len + 1));
	cmd->file = malloc(sizeof(char *) * (fl_len + 1));
	if (command->cmnd)
	{
		cmd->cmd[i++] = strdup(command->cmnd);
		free(command->cmnd);
	}
	return (i);
}

void	ft_free_oldlist(t_command *command)
{
	t_command	*temp;
	t_red		*temp_red;
	t_argument	*temp_arg;

	while (command)
	{
		temp = command;
		while (command->argument)
		{
			temp_arg = command->argument;
			command->argument = command->argument->next;
			free(temp_arg);
		}
		while (command->red)
		{
			temp_red = command->red;
			command->red = command->red->next;
			free(temp_red);
		}
		command = command->next;
		free(temp);
	}
}

void	ft_execut(t_commnd *cmd, t_command *command, t_all *all, char **envp)
{
	cmd = ft_transfer_cmd(command);
	ft_free_oldlist(command);
	check_heredoc(cmd, &all->heredocc);
	if (ft_lstsize_cmd(cmd) == 1)
		exec_first_cmd(cmd, envp, &all->heredocc, all);
	else if (ft_lstsize_cmd(cmd) >= 2)
		exec_2_cmd(cmd, envp, &all->heredocc, all);
	while (all->heredocc)
	{
		close(all->heredocc->fd_pipe_heredoc);
		all->heredocc = all->heredocc->next;
	}
	ft_free_cmd(cmd);
	all->heredocc = NULL;
}

int	main(int ac, char **av, char **envp)
{
	char		*readl;
	t_command	*command;
	t_commnd	*cmd;
	t_all		*all;

	(void)av;
	if (ac > 1)
		return (0);
	all = ft_all_init(envp);
	cmd = NULL;
	while (1)
	{
		signalsss(&readl);
		add_history(readl);
		readl = ft_expand_var(readl, 0);
		command = ft_command(readl);
		if (!command)
			continue ;
		if (ft_clean_command(command) == -1)
		{
			ft_free_oldlist(command);
			continue ;
		}
		ft_execut(cmd, command, all, envp);
	}
}
