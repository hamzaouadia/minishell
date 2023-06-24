#include "minishell.h"

int	ft_exp_check(char c)
{
	if ((c >= 42 && c <= 47) || c == ' ' || c == '\t' || c == 0
		|| c == '|' || (c >= 58 && c <= 62))
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

int	ft_count_red(char *en)
{
	int	i;
	int	red;

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

void	ft_protect_var(char *en, int len, int x)
{
	if ((strchr(en, '>') || strchr(en, '<')) && x == 1)
		g_global.exp_len = len + ft_count_red(en);
}

