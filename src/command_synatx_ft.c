#include "minishell.h"

int ft_white_spaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
    return (i);
}

int	command_argument(char *str, int i, t_command *command)
{
	t_argument	*head_ar;
	t_red		*head_red;
	int			len;
	int			j;

	head_ar = command->argument;
	head_red = command->red;
	while (str[i])
	{
		j = 0;
		i = ft_white_spaces(str, i);
		if (str[i] == '\0' || str[i] == '|')
			break ;
		if (str[i] == '<' || str[i] == '>')
		{
			len = ft_spchar_len(str + i, '<', '>');
			head_red->rd = calloc((len + 1), sizeof(char));
			head_red->rd[j] = '\0';
			while (len > j)
				head_red->rd[j++] = str[i++];
			i = ft_white_spaces(str, i);
			if (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
			{
				i = ft_white_spaces(str, i);
				j = 0;
				len = ft_arg_len(str + i);
				head_red->fl = calloc((len + 1), sizeof(char));
				while (len > j)
					head_red->fl[j++] = str[i++];
				head_red->fl[j] = '\0';
				i = ft_white_spaces(str, i);
			}
			else
            {
                printf("-bash: syntax error near unexpected token\n");
                g_global.exit_code = 258;
                return (-1);
            }
			if (str[i] && str[i] != '<' && str[i] != '>'
				&& command->cmnd == NULL && str[i] != '|')
			{
				i = ft_white_spaces(str, i);
				j = 0;
				len = ft_arg_len(str + i);
				command->cmnd = calloc((len + 1), sizeof(char));
				while (len > j)
					command->cmnd[j++] = str[i++];
				i = ft_white_spaces(str, i);
			}
			head_red->next = ft_lstnew_red(NULL);
			head_red = head_red->next;
		}
		else
		{
			len = ft_arg_len(str + i);
			head_ar->arg = calloc((len + 1), sizeof(char));
			while (len > j)
				head_ar->arg[j++] = str[i++];
			head_ar->arg[j] = '\0';
			head_ar->next = ft_lstnew_arg(NULL);
			head_ar = head_ar->next;
		}
	}
	return (i);
}

int	command_syntax(char *str, int i, t_command *command)
{
	int	len;
	int	j;

	j = 0;
	i = ft_white_spaces(str, i);
	len = ft_arg_len(str + i);
	if (len != 0)
	{
		command->cmnd = calloc((len + 1), sizeof(char));
		while (len > j)
			command->cmnd[j++] = str[i++];
		command->cmnd[j] = '\0';
	}
	i = command_argument(str, i, command);
	return (i);
}

t_command	*ft_command(char *str)
{
	t_command	*command;
	t_command	*head;
	int			i;

	command = ft_cmndnew(NULL);
	head = command;
	i = 0;
	while (str[i])
	{
		i = ft_white_spaces(str, i);
		if (str[i] == '|')
			head->pipe = str[i++];
		i = command_syntax(str, i, head);
        if  (i == -1)
        {
            free (str);
		    ft_free_oldlist(command);
            return (NULL);
        }
		i = ft_white_spaces(str, i);
		head->next = ft_cmndnew(NULL);
		head = head->next;
	}
	free(str);
	return (command);
}
