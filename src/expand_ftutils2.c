#include "minishell.h"

int	ft_exp_check(char c)
{
	if ((c >= 43 && c <= 47) || c == ' ' || c == 0
		|| c == '|' || c == '>' || c == '<')
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
