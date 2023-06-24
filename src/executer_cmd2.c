/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:12:39 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/24 16:12:44 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_one_cmd(t_commnd *cmd, char **envp, t_all *all,
		t_heredoc **heredocc)
{
	char	*c;

	open_files(cmd, all->fds, heredocc);
	if (all->fds->fd_in != -1)
		(dup2(all->fds->fd_in, 0), close(all->fds->fd_in));
	if (all->fds->fd_out != -1)
		(dup2(all->fds->fd_out, 1), close(all->fds->fd_out));
	if (cmd->cmd[0])
	{
		c = check_path(all->lst, cmd);
		if (!c)
			print_errors_path();
		else
		{
			(execve(c, cmd->cmd, envp), print_errors_exceve());
		}
	}
	else
		exit(0);
}

void	exec_first_cmd_in_pipe(t_commnd *cmd, t_heredoc **heredocc, char **envp,
		t_all *all)
{
	open_files(cmd, all->fds, heredocc);
	close(all->utils->fd_pipe[0]);
	if (all->fds->fd_in != -1)
		dup2(all->fds->fd_in, 0);
	if (all->fds->fd_out != -1)
		dup2(all->fds->fd_out, 1);
	else
		dup2(all->utils->fd_pipe[1], 1);
	close(all->utils->fd_pipe[1]);
	if (cmd->cmd[0])
	{
		if (check_builtins(cmd) == 0)
		{
			execve(check_path(all->lst, cmd), cmd->cmd, envp);
			print_errors_exceve();
		}
		else
		{
			exec_builtins(cmd, all->lst);
			exit(0);
		}
	}
	else
		exit(0);
}

void	exec_cmd_west(t_commnd *cmd, t_heredoc *heredocc, t_all *all,
		char **envp)
{
	open_files(cmd, all->fds, &heredocc);
	if (all->fds->fd_in != -1)
		dup2(all->fds->fd_in, 0);
	else
		dup2(all->utils->stock_pipe, 0);
	if (all->fds->fd_out != -1)
		dup2(all->fds->fd_out, 1);
	else
		dup2(all->utils->fd_pipe[1], 1);
	close_pipes(all->utils);
	if (cmd->cmd[0])
	{
		if (check_builtins(cmd) == 0)
		{
			execve(check_path(all->lst, cmd), cmd->cmd, envp);
			print_errors_exec();
		}
		else
		{
			exec_builtins(cmd, all->lst);
			exit(0);
		}
	}
	else
		exit(0);
}

void	last_cmd(t_commnd *cmd, t_heredoc *heredocc, char **envp, t_all *all)
{
	open_files(cmd, all->fds, &heredocc);
	if (all->fds->fd_in != -1)
		dup2(all->fds->fd_in, 0);
	else
		dup2(all->utils->fd_pipe[0], 0);
	if (all->fds->fd_out != -1)
		dup2(all->fds->fd_out, 1);
	close(all->utils->fd_pipe[1]);
	close(all->utils->fd_pipe[0]);
	if (cmd->cmd)
	{
		if (check_builtins(cmd) == 0)
		{
			execve(check_path(all->lst, cmd), cmd->cmd, envp);
			write(2, "bash: command not found\n", 25);
			exit(127);
		}
		else
		{
			exec_builtins(cmd, all->lst);
			exit(0);
		}
	}
	else
		exit(0);
}

void	helper1(t_commnd *cmd, char **envp, t_all *all, t_heredoc **heredocc1)
{
	t_heredoc	*heredocc;

	heredocc = *heredocc1;
	if (check_find_herdoc(&cmd, 0) && check_find_herdoc(&cmd->next, 0))
		heredocc = heredocc->next;
	cmd = cmd->next;
	while (cmd->next->cmd)
	{
		helper2(all->fds, all->utils);
		all->utils->pid_fork = fork();
		if (all->utils->pid_fork == 0)
			exec_cmd_west(cmd, heredocc, all, envp);
		cmd = cmd->next;
		if (check_find_herdoc(&cmd, 0))
			heredocc = heredocc->next;
	}
	initi_fds(all->fds);
	close_pipe2(all->utils);
	all->utils->pid_fork = fork();
	if (all->utils->pid_fork == 0)
		last_cmd(cmd, heredocc, envp, all);
	close_pipes(all->utils);
	waitpid(all->utils->pid_fork, NULL, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
}
