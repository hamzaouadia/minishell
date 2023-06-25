/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_sigs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:19:14 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/25 03:19:17 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandle(int sig)
{
	(void)sig;
	g_global.exit_code = 1;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signalsss(char **cmd_line)
{
	struct termios	term;
	struct termios	oldterm;

	signal(SIGINT, sighandle);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(0, &term);
	tcgetattr(0, &oldterm);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	*cmd_line = readline("minishell$ ");
	if (!(*cmd_line))
		exit (0);
	tcsetattr(0, TCSANOW, &oldterm);
}
