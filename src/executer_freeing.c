/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_freeing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:34:32 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:35:53 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_commnd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		ft_free_ddim(cmd->cmd);
		ft_free_ddim(cmd->file);
		cmd = cmd->next;
	}
}

void	ft_free_ddim(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
