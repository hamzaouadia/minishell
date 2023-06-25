/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haouadia <haouadia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 02:41:06 by haouadia          #+#    #+#             */
/*   Updated: 2023/06/25 02:41:08 by haouadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fill_exp(char *exp, char *en, int j, int x)
{
	int	k;

	k = 0;
	while (en[k])
	{
		if ((en[k] == '>' || en[k] == '<' ) && x == 1)
		{
			exp[j++] = '"';
			while (en[k] == '>' || en[k] == '<')
				exp[j++] = en[k++];
			exp[j++] = '"';
		}
		else
			exp[j++] = en[k++];
	}
	exp[j] = '\0';
	return (exp);
}

char	*ft_new_arg(char *arg, int i, char *en, int x)
{
	char	*new;
	char	*exp;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (en[len])
		len++;
	g_global.exp_len = len;
	ft_protect_var(en, len, x);
	exp = calloc((g_global.exp_len + i + 1), sizeof(char));
	len = 0;
	while (len < i)
		exp[j++] = arg[len++];
	len++;
	while (arg[len] && ft_exp_del(arg[len]) == 0)
		len++;
	exp = ft_fill_exp(exp, en, j, x);
	if (x == 2)
		len++;
	new = ft_strjoin(exp, arg + len);
	free(arg);
	free(exp);
	return (new);
}

char	*ft_remove_var(char *arg, int i)
{
	int		j;
	int		len;
	char	*exp;
	char	*new;

	j = -1;
	len = 1;
	exp = calloc(i + 1, sizeof(char));
	while (++j < i)
		exp[j] = arg[j];
	exp[j] = '\0';
	while (arg[len + i] && ft_exp_del(arg[len + i]) == 0)
		len++;
	if (arg[len + i] == '$')
		len++;
	new = ft_strjoin(exp, arg + i + len);
	free(arg);
	free(exp);
	return (new);
}

char    *ft_check_cond(char *arg, int i)
{
    char *code;

    if (arg[i + 1] == '?')
    {
        code = ft_itoa(g_global.exit_code);
        arg = ft_new_arg(arg, i, code, 2);
        free(code);
    }
    else if (ft_exp_check(arg[i + 1]) == 0 || arg[i + 1] == '$')
        arg = ft_remove_var(arg, i);
    return (arg);
}

char    *ft_check_var(char *arg, int i, int x)
{
    int        j;
    int        k;
    t_env      *temp;

    temp = g_global.env;
    while (temp)
    {
        k = 0;
        j = i + 1;
        while (arg[j] == temp->key[k])
        {
            if (temp->key[k] == '\0')
                break ;
            j++;
            k++;
        }
        if (ft_exp_del(arg[j]) == 1 && temp->key[k] == '\0')
        {
            arg = ft_new_arg(arg, i, temp->value, x);
            return (arg);
        }
        temp = temp->next;
    }
    arg = ft_check_cond(arg, i);
    return (arg);
}
