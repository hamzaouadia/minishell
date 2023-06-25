/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_linkedlist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 03:18:52 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/25 03:18:55 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_front(t_env **lst, t_env *new)
{
	if (!*lst)
	{
		(*lst) = new;
		(*lst)->next = NULL;
	}
	else
	{
		new->next = (*lst);
		(*lst) = new;
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*new_node;

	new_node = NULL;
	if (!*lst)
	{
		(*lst) = new;
		(*lst)->next = NULL;
	}
	else
	{
		new_node = ft_lstlast(*lst);
		new_node->next = new;
	}
}

t_heredoc	*ft_lstlast_herdoc(t_heredoc **lst)
{
	t_heredoc	*current;

	if (!lst)
		return (NULL);
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ft_lstadd_back_heredoc(t_heredoc **heredocc, t_heredoc *new)
{
	t_heredoc	*new_node;

	new_node = NULL;
	if (!(*heredocc))
	{
		(*heredocc) = new;
		(*heredocc)->next = NULL;
	}
	else
	{
		new_node = ft_lstlast_herdoc(heredocc);
		new_node->next = new;
	}
}
