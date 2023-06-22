#include "minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

int	ft_lstsize(t_env *lst)
{
	t_env	*head;
	int		count;

	count = 0;
	head = lst;
	while (head != NULL)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	ft_lstsize_cmd(t_commnd *lst)
{
	t_commnd	*head;
	int			count;

	count = 0;
	head = lst;
	while (head->next != NULL)
	{        
		count++;
		head = head->next;
	}
	return (count);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
