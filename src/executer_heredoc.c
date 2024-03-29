/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:36:01 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/25 03:24:27 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_herdocc(t_heredoc **heredocc)
{
	t_heredoc	*temp;

	while ((*heredocc))
	{
		temp = (*heredocc);
		(*heredocc) = (*heredocc)->next;
		free(temp);
	}
	free(heredocc);
}

int	count_heredoc(t_commnd *cmd)
{
	t_commnd	*head;
	int			counter;
	int			i;

	head = cmd;
	counter = 0;
	while (cmd->next)
	{
		i = 0;
		while (cmd->file && cmd->file[i])
		{
			if (ft_strcmp(cmd->file[i], "<<") == 0)
				counter++;
			i++;
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (counter);
}

int	check_find_herdoc(t_commnd **cmd, int i)
{
	t_commnd	*tmp;

	tmp = *cmd;
	while (tmp->file && tmp->file[i])
	{
		if (ft_strcmp(tmp->file[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	read_heredoc(char *delimit, t_heredoc **heredocc, int i, t_commnd *cmd)
{
	char	*heredoc;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		heredoc = readline("< ");
		if (ft_strcmp(heredoc, delimit) == 0)
		{
			free(heredoc);
			break ;
		}
		heredoc = ft_expand_var(heredoc, 1);
		write(fd[1], heredoc, ft_strlen(heredoc));
		write(fd[1], "\n", 1);
		free(heredoc);
	}
	close(fd[1]);
	if (check_find_herdoc(&cmd, i))
		close(fd[0]);
	else
		ft_lstadd_back_heredoc(heredocc, ft_lstnew_heredoc(fd[0]));
}

void	check_heredoc(t_commnd *cmd, t_heredoc **heredoc)
{
	t_commnd	*head;
	int			i;
	int			num_heredoc;
	char		*delimit;

	head = cmd;
	i = 0;
	num_heredoc = count_heredoc(cmd);
	if (num_heredoc > 16)
		print_erros_heredoc();
	while (head->next)
	{
		i = 0;
		while (head->file[i])
		{
			if (ft_strcmp(head->file[i], "<<") == 0)
			{
				delimit = head->file[i + 1];
				read_heredoc(delimit, heredoc, i + 1, head);
			}
			i++;
		}
		head = head->next;
	}
}
