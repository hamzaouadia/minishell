#include "minishell.h"

int	ft_syntax_red(t_red *red)
{
	int	i;

	while (red->next)
	{
		i = 0;
		if (red->rd == NULL)
			return (0);
		i = strlen(red->rd);
		if (i > 2 || (red->rd[0] == '>' && red->rd[1] == '<'))
		{
			printf("-bash: syntax error near unexpected token\n");
			g_global.exit_code = 258;
			return (-1);
		}
		red = red->next;
	}
	return (0);
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

int	ft_clean_arg_red(t_argument *argument, t_red *red)
{
	while (argument->next)
	{
		if (ft_quotes_syntax(argument->arg) == -1)
			return (-1);
		argument->arg = ft_clean_quotes(argument->arg);
		argument = argument->next;
	}
	while (red->next)
	{
		if (ft_quotes_syntax(red->fl) == -1)
			return (-1);
		red->fl = ft_clean_quotes(red->fl);
		red = red->next;
	}
	return (0);
}

int	ft_syntax_condition(t_command *command)
{
	if (command->pipe != '\0' && !command->cmnd
		&& !command->argument->arg && !command->red->rd)
	{
		printf("-bash: syntax error\n");
		g_global.exit_code = 258;
		return (-1);
	}
	if (ft_syntax_red(command->red) == -1)
		return (-1);
	return (0);
}

int	ft_clean_command(t_command *command)
{
	t_command	*head_cmd;

	head_cmd = command;
	if (head_cmd->pipe != '\0')
	{
		printf("-bash: syntax error\n");
		g_global.exit_code = 258;
		return (-1);
	}
	while (head_cmd->next)
	{
		if (ft_syntax_condition(head_cmd) == -1)
			return (-1);
		head_cmd->cmnd = ft_clean_quotes(head_cmd->cmnd);
		if (ft_clean_arg_red(head_cmd->argument, head_cmd->red) == -1)
			return (-1);
		head_cmd = head_cmd->next;
	}
	return (0);
}
