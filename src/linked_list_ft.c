/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_ft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:41:56 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 02:41:58 by haouadia         ###   ########.fr       */
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
