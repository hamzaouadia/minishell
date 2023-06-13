#include "minishell.h"

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
	int		ex;
	char	q;

	len = -1;
	ex = 0;
	while (str[++len])
	{
		if (str[len] == '"' || str[len] == '\'')
		{
			q = str[len++];
			while (str[len] && str[len] != q)
				len++;
		}
		if (str[len] == ' ' || str[len] == '|'
			|| str[len] == '>' || str[len] == '<')
			break ;
	}
	return (len + ex);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = (char *)malloc(sizeof(char) * (i + j) + 1);
	if (!join)
		return (NULL);
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (join - i - j);
}

int	ft_exp_del(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (0);
	return (1);
}

char	*ft_new_arg(char *arg, int i, char *en)
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
	g.exp_len = len;
	exp = malloc(sizeof(char) * (len + i + 1));
	len = 0;
	while (len < i)
		exp[j++] = arg[len++];
	len++;
	while (arg[len] && ft_exp_del(arg[len]) == 0)
		len++;
	while (en[k])
		exp[j++] = en[k++];
	exp[j] = '\0';
	new = ft_strjoin(exp, arg + len);
	free(arg);
	free(exp);
	return (new);
}

char	*ft_check_var(char *arg, int i)
{
	int	j;
	int	k;
	int	e;

	e = 0;
	while (g.environ[e])
	{
		k = 0;
		j = i + 1;
		while (arg[j] == g.environ[e][k])
		{
			j++;
			k++;
		}
		if (ft_exp_del(arg[j]) == 1 && g.environ[e][k] == '=')
		{
			arg = ft_new_arg(arg, i, g.environ[e] + k + 1);
			return (arg);
		}
		e++;
	}
	return (arg);
}

char	*ft_expand_var(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
		{
			i++;
			while (arg[i] && arg[i] != '"')
			{
				if (arg[i] == '$')
				{
					arg = ft_check_var(arg, i);
					i = i + g.exp_len;
				}
				else
					i++;
			}
		}
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
				i++;
		}
		if (arg[i] == '$')
		{
			arg = ft_check_var(arg, i);
			i = i + g.exp_len;
		}
		else
			i++;
	}
	return (arg);
}
