#include "minishell.h"

void	put_str(char *string, long long int nb, int size)
{
	if (nb == 0)
		string[0] = '0';
	else if (nb < 0)
	{
		nb *= -1;
		string[0] = '-';
	}
	size--;
	while (size >= 0 && nb != 0)
	{
		string[size] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
}

int	string_size(long long int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i ++;
	}
	if (nb != 0)
	{
		while (nb != 0)
		{
			nb = nb / 10;
			i++;
		}
	}
	else
		i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*string;
	long long int	nb;
	int				size;

	nb = n;
	size = string_size(nb);
	string = (char *)malloc(sizeof(char) * size + 1);
	if (!string)
		return (NULL);
	put_str(string, nb, size);
	string[size] = '\0';
	return (string);
}

int	ft_spchar_len(char *str, char d1, char d2)
{
	int	len;

	len = 0;
	if (!d1)
		d1 = d2;
	else if (!d2)
		d2 = d1;
	while (str[len] && (str[len] == d1 || str[len] == d2))
		len++;
	return (len);
}

int	ft_arg_len(char *str)
{
	int		len;
	char	q;

	len = -1;
	while (str[++len])
	{
		if (str[len] == '"' || str[len] == '\'')
		{
			q = str[len++];
			while (str[len] && str[len] != q)
				len++;
		}
		if (str[len] == ' ' || str[len] == '|' || str[len] == '>' || str[len] == '<' || !str[len])
			break ;
	}
	return (len);
}

int	ft_exp_check(char c)
{
	if ((c >= 43 && c <= 47) || c == ' ' || c == 0 || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_exp_del(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_')
		return (0);
	return (1);
}

int ft_count_red(char *en)
{
    int i;
    int red;

    i = 0;
    red = 0;
    while (en[i])
    {
        if (en[i] == '>' || en[i] == '<')
        {
            red += 2;
            while (en[i] == '>' || en[i] == '<')
                i++;
        }
        else
            i++;
    }
    return (red);
}

char	*ft_new_arg(char *arg, int i, char *en, int x)
{
	char	*new;
	char	*exp;
	int		len;
	int		j;
	int		k;

	len = 0;
	j = 0;
	k = 0;
	while (en[len])
		len++;    
    g_global.exp_len = len;
    if ((strchr(en, '>') || strchr(en, '<')) && x == 1)
        g_global.exp_len = len + ft_count_red(en);
	exp = calloc((g_global.exp_len + i + 1), sizeof(char));
	len = 0;
	while (len < i)
		exp[j++] = arg[len++];
	len++;
	while (arg[len] && ft_exp_del(arg[len]) == 0)
		len++;
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
    if (x == 2)
		len++;
	new = ft_strjoin(exp, arg + len);
	free(arg);
	free(exp);
	return (new);
}

char    *ft_remove_var(char *arg, int i)
{
    int     j;
    int     len;
    char    *exp;
    char    *new;

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

char	*ft_check_var(char *arg, int i, int x)
{
	int	j;
	int	k;
	int	e;
    char    *code;
	e = 0;
	while (g_global.en[e])
	{
		k = 0;
		j = i + 1;
		while (arg[j] == g_global.en[e][k])
		{
            if (g_global.en[e][k] == '=')
                break ;
			j++;
			k++;
		}
		if (ft_exp_del(arg[j]) == 1 && g_global.en[e][k] == '=')
		{
			arg = ft_new_arg(arg, i, g_global.en[e] + k + 1, x);
			return (arg);
		}
		e++;
	}
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

char	*ft_expand_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
        g_global.exp_len = 0;
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
		}
		if (arg[i] == '"')
		{
			i++;
			while (arg[i] && arg[i] != '"')
			{
				if (arg[i] == '$' && (ft_exp_check(arg[i + 1]) == 0 || arg[i + 1] == '$'))
                {
					arg = ft_check_var(arg, i, 0);
                    i = i + g_global.exp_len;
                }
				else
					i++;
			}
		}
		if (arg[i] == '$' && (ft_exp_check(arg[i + 1]) == 0 || arg[i + 1] == '$'))
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
	int i;
	char *str1;
	char *str2;
	char *str3;
	char *str4;
	char **en;
	t_env *tmp;

	tmp =  *env;
	i = 0;
	while (*env)
	{
		*env = (*env)->next;
		i++;
	}
	*env = tmp;
	en = ft_calloc(i + 1 ,sizeof(char *));
	i = 0;
	while (*env)
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
