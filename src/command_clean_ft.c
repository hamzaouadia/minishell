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

int	ft_quotes_syntax(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (str == NULL)
		return 0;
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
				g_global.exit_code = 258;
                return (-1);
			}
		}
		i++;
	}
    return 0;
}

int	ft_syntax_red(t_red *red)
{
	int	i;

	while (red->next)
	{
		i = 0;
		if (red->rd == NULL)
			return 0;
		i = strlen(red->rd);
		if (i > 2 || (red->rd[0] == '>' && red->rd[1] == '<'))
		{
			printf("-bash: syntax error near unexpected token\n");
			g_global.exit_code = 258;
            return (-1);
		}
		red = red->next;
	}
    return 0;
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
		return (NULL);
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

int	ft_clean_command(t_command *command)
{
	t_command	*head_cmd;
	t_argument	*head_arg;
	t_red		*head_red;

	head_cmd = command;
	if (command->pipe != '\0')
	{
		printf("-bash: syntax error\n");
		g_global.exit_code = 258;
        return (-1);
	}
	while (command->next)
	{
		if (command->pipe != '\0' && !command->cmnd
		&& !command->argument->arg && !command->red->rd)
        {
            printf("-bash: syntax error\n");
            g_global.exit_code = 258;
            return (-1);
        }
		head_arg = command->argument;
		head_red = command->red;
		if (ft_syntax_red(command->red) == -1)
            return -1;
		command->cmnd = ft_clean_quotes(command->cmnd);
		while (command->argument->next)
		{
			if (ft_quotes_syntax(command->argument->arg) == -1)
                return -1;
			command->argument->arg = ft_clean_quotes(command->argument->arg);
			command->argument = command->argument->next;
		}
		while (command->red->next)
		{
			if (ft_quotes_syntax(command->red->fl))
                return -1;
			command->red->fl = ft_clean_quotes(command->red->fl);
			command->red = command->red->next;
		}
		command->argument = head_arg;
		command->red = head_red;
		command = command->next;
	}
	command = head_cmd;
    return (0);
}
