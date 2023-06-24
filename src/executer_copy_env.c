/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_copy_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 09:23:29 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/23 09:24:58 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_str(char **str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		count++;
		i++;
	}
	return (count);
}

t_env	*copy_env(char **envp, t_env **lst)
{
	int	i;

	i = len_str(envp) - 1;
	if (!envp || !envp[0])
	{
		ft_lstadd_front(lst, ft_lstnew("PWD", getcwd(NULL, 0)));
		ft_lstadd_front(lst, ft_lstnew("SHLVL", "1"));
		ft_lstadd_front(lst, ft_lstnew("_", "/usr/bin/env"));
		sort_export(*lst);
	}
	else
	{
		while (i >= 0)
		{
			ft_lstadd_front(lst, ft_lstnew(
					ft_substr(envp[i], 0, ft_len(envp[i], '=')),
					ft_substr(envp[i], ft_len(envp[i], '=') + 1,
						ft_len(envp[i], '\0'))
					));
			i--;
		}
	}
	return (*lst);
}
