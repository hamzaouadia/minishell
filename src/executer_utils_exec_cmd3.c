/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils_exec_cmd3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:47:30 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:47:32 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe2(t_utils *utils)
{
	close(utils->fd_pipe[1]);
	close(utils->stock_pipe);
}

void	close_pipes(t_utils *utils)
{
	close(utils->fd_pipe[0]);
	close(utils->fd_pipe[1]);
}

void	helper2(t_fds *fds, t_utils *utils)
{
	initi_fds(fds);
	(utils->stock_pipe != -1) && close(utils->stock_pipe);
	close(utils->fd_pipe[1]);
	utils->stock_pipe = utils->fd_pipe[0];
	pipe(utils->fd_pipe);
}

void	print_erros_heredoc(void)
{
	write(2, "bash: maximum here-document count exceeded", 43);
	g_global.exit_code = 2;
	exit(2);
}
