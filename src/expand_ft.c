#include "minishell.h"

char    *ft_fill_exp(char *exp, char *en, int j, int x)
{
    int k;

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

void    ft_protect_var(char *en, int len, int x)
{
    if ((strchr(en, '>') || strchr(en, '<')) && x == 1)
		g_global.exp_len = len + ft_count_red(en);
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

char    *ft_remove_and_excode(char *arg, int i)
{
	char	*code;

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

char	*ft_check_var(char *arg, int i, int x)
{
	int		j;
	int		k;
	int		e;

	e = -1;
	while (g_global.en[++e])
	{
		k = 0;
		j = i + 1;
		while (arg[j++] == g_global.en[e][k])
		{
			if (g_global.en[e][k] == '=')
				break ;
			k++;
		}
		if (ft_exp_del(arg[j]) == 1 && g_global.en[e][k] == '=')
		{
            printf("***%c***\n",arg[j]);
			arg = ft_new_arg(arg, i, g_global.en[e] + k + 1, x);
			return (arg);
		}
	}
	arg = ft_remove_and_excode(arg, i);
	return (arg);
}
int ft_expand_condition(char *arg, int i)
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

int ft_singl_Qexp(char *arg, int i, int ex)
{
    if (arg[i] == '\'' && ex == 0)
	{
		i++;
		while (arg[i] && arg[i] != '\'')
			i++;
	}
    return (i);
}

char *ft_double_Qexp(char *arg, int *i)
{
    if (arg[*i] == '"')
	{
		while (arg[*i] && arg[++(*i)] != '"')
		{
			if (arg[*i] == '$' && (ft_exp_check(arg[*i + 1]) == 0
					|| arg[*i + 1] == '$'))
			{
				arg = ft_check_var(arg, *i, 0);
				*i = *i + g_global.exp_len;
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
		i = ft_singl_Qexp(arg, i, ex);
		arg = ft_double_Qexp(arg, &i);
		i = ft_expand_condition(arg, i);
		if (arg[i] == '$' && (ft_exp_check(arg[i + 1]) == 0
				|| arg[i + 1] == '$'))
		{
			arg = ft_check_var(arg, i, 1);
			i = i + g_global.exp_len;
		}
		else if (arg[i])
			i++;
	}
	return (arg);
}

char	**nodes_counter(t_env **env)
{
	int		i;
	char	*str1;
	char	*str2;
	char	*str3;
	char	*str4;
	char	**en;
	t_env	*tmp;

	tmp = *env;
	i = 0;
	while (*env)
	{
		*env = (*env)->next;
		i++;
	}
	*env = tmp;
	en = ft_calloc(i + 1, sizeof(char *));
	i = 0;
    tmp = *env;
	while ((*env))
	{
		str1 = ft_strdup((*env)->value);
		str2 = ft_strdup((*env)->key);
		str3 = ft_strjoin(str2, "=");
		str4 = ft_strjoin(str3, str1);
		en[i] = ft_strdup(str4);
		i++;
		(*env) = (*env)->next;
		free(str1);
		free(str2);
		free(str3);
		free(str4);
	}
	en[i] = NULL;
	*env = tmp;
	return (en);
}
