#include "minishell.h"

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
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0' || str[i] == '|')
			break ;
		if (str[i] == '<' || str[i] == '>')
		{
			len = ft_spchar_len(str + i, '<', '>');
			command->red->rd = calloc((len + 1), sizeof(char));
			command->red->rd[j] = '\0';
			while (len > j)
				command->red->rd[j++] = str[i++];
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				j = 0;
				len = ft_arg_len(str + i);
				command->red->fl = calloc((len + 1), sizeof(char));
				while (len > j)
					command->red->fl[j++] = str[i++];
				command->red->fl[j] = '\0';
				while (str[i] == ' ' || str[i] == '\t')
					i++;
			}
			else
			{
				printf("-bash: syntax error near unexpected token\n");
				exit (0);
			}
			if (str[i] && str[i] != '<' && str[i] != '>'
				&& command->cmnd == NULL && str[i] != '|')
			{
				while (str[i] == ' ' || str[i] == '\t')
					i++;
				j = 0;
				len = ft_arg_len(str + i);
				command->cmnd = calloc((len + 1), sizeof(char));
				while (len > j)
					command->cmnd[j++] = str[i++];
				while (str[i] == ' ' || str[i] == '\t')
					i++;
			}
            command->red->next = ft_lstnew_red(NULL);
			command->red = command->red->next;
		}
		else
		{
			len = ft_arg_len(str + i);
			command->argument->arg = calloc((len + 1), sizeof(char));
			while (len > j)
				command->argument->arg[j++] = str[i++];
			command->argument->arg[j] = '\0';
			command->argument->next = ft_lstnew_arg(NULL);
			command->argument = command->argument->next;
		}
	}
	command->argument = head_ar;
	command->red = head_red;
	return (i);
}

int	command_syntax(char *str, int i, t_command *command)
{
	int	len;
	int	j;

	j = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
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
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '|')
			command->pipe = str[i++];
		i = command_syntax(str, i, command);
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		command->next = ft_cmndnew(NULL);
		command = command->next;
	}
    command = head;
	return (command);
}
