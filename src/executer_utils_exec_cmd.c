/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_exec_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:47:13 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:47:16 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files_helper(t_commnd *cmd, t_fds *fds, int i)
{
	if (ft_strcmp(cmd->file[i], "<") == 0)
	{
		fds->fd_in = open(cmd->file[i + 1], O_RDONLY, 0644);
		if (fds->fd_in == -1)
			print_errors_files();
	}
	else if (ft_strcmp(cmd->file[i], ">") == 0)
	{
		fds->fd_out = open(cmd->file[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (fds->fd_out == -1)
			print_errors_files();
	}
}

void	print_errors_fork(void)
{
	write(2, "error in fork\n", 15);
	exit(127);
}

void	print_errors_path(void)
{
	write(2, "minishell: command not found\n", 30);
	g_global.exit_code = 127;
	exit(1);
}

void	print_errors_exceve(void)
{
	write(2, "minishell: command not found\n", 30);
	g_global.exit_code = 127;
	exit(127);
}

void	initi_fds(t_fds *fds)
{
	fds->fd_in = -1;
	fds->fd_out = -1;
}
