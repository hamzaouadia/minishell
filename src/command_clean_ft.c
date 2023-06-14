#include "minishell.h"

int	ft_quotes_len(char *str)
{
	int		i;
	int		quotes;
	char	q;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quotes++;
			q = str[i++];
			while (str[i] != q && str[i])
				i++;
		}
		i++;
	}
	return (quotes);
}

void	ft_quotes_syntax(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			q = str[i++];
			while (str[i] != q && str[i])
				i++;
			if (str[i] == '\0')
			{
				printf("-bash: syntax error\n");
				exit (0);
			}
		}
		i++;
	}
}

void	ft_syntax_red(t_red *red)
{
	int	i;

	while (red->next)
	{
		i = 0;
		if (red->rd == NULL)
			return ;
		i = strlen(red->rd);
		if (i > 2 || (red->rd[0] == '>' && red->rd[1] == '<'))
		{
			printf("-bash: syntax error near unexpected token\n");
			exit (0);
		}
		red = red->next;
	}
}

char	*ft_clean_quotes(char *arg)
{
	char	*new;
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
    if (!arg)
        return NULL;
	new = malloc(sizeof(char) * (strlen(arg) - ft_quotes_len(arg) + 1));
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			q = arg[i++];
			while (arg[i] != q && arg[i])
				new[j++] = arg[i++];
		}
		else
			new[j++] = arg[i];
		i++;
	}
	new[j] = '\0';
	free(arg);
	return (new);
}

void	ft_clean_command(t_command *command)
{
	t_command	*head_cmd;
	t_argument	*head_arg;
	t_file		*head_file;

	head_cmd = command;
	if (command->pipe != '\0')
	{
		printf("-bash: syntax error\n");
		exit (0);
	}
	while (command->next)
	{
        head_arg = command->argument;
        head_file = command->file;
		ft_syntax_red(command->red);
		command->cmnd = ft_clean_quotes(command->cmnd);
		while (command->argument->next)
		{
			ft_quotes_syntax(command->argument->arg);
			command->argument->arg = ft_clean_quotes(command->argument->arg);
			command->argument = command->argument->next;
		}
		while (command->file->next)
		{
			ft_quotes_syntax(command->file->fl);
			command->file->fl = ft_clean_quotes(command->file->fl);
			command->file = command->file->next;
		}
	    command->argument = head_arg;
	    command->file = head_file;
		command = command->next;
	}
	command = head_cmd;
}
