/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ftutils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:41:39 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 03:27:23 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expand_condition(char *arg, int i)
{
	if (arg[i] == '<' && arg[i + 1] == '<')
	{
		while (arg[i] && arg[i] == '<')
			i++;
		while (arg[i] && arg[i] == ' ')
			i++;
		while (arg[i] && arg[i] != ' ')
			i++;
	}
	return (i);
}

int	ft_singl_qexp(char *arg, int i, int ex)
{
	if (arg[i] == '\'' && ex == 0)
	{
		i++;
		while (arg[i] && arg[i] != '\'')
			i++;
	}
	return (i);
}

char	*ft_double_qexp(char *arg, int *i)
{
	if (arg[*i] == '"')
	{
		(*i)++;
		while (arg[*i] && arg[*i] != '"')
		{
			if (arg[*i] == '$' && (ft_exp_check(arg[*i + 1]) == 0 || arg[*i
						+ 1] == '$'))
			{
				arg = ft_check_var(arg, *i, 0);
				*i += +g_global.exp_len;
			}
			else
				(*i)++;
		}
	}
	return (arg);
}

char	*ft_expand_var(char *arg, int ex)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		g_global.exp_len = 0;
		i = ft_singl_qexp(arg, i, ex);
		arg = ft_double_qexp(arg, &i);
		i = ft_expand_condition(arg, i);
		if (arg[i] == '$' && (ft_exp_check(arg[i + 1]) == 0 || arg[i
					+ 1] == '$'))
		{
			arg = ft_check_var(arg, i, 1);
			i = i + g_global.exp_len;
		}
		else if (arg[i])
			i++;
	}
	return (arg);
}

int	ft_env_len(t_env **env)
{
	int		i;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	while (*env)
	{
		*env = (*env)->next;
		i++;
	}
	*env = tmp;
	return (i);
}
