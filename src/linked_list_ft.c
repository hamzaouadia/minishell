#include "minishell.h"

t_file	*ft_lstnew_file(void *fl)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		exit (0);
	file->fl = fl;
	file->next = NULL;
	return (file);
}

t_red	*ft_lstnew_red(void *rd)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		exit (0);
	red->rd = rd;
	red->next = NULL;
	return (red);
}

t_option	*ft_lstnew_opt(void *opt)
{
	t_option	*option;

	option = malloc(sizeof(t_option));
	if (!option)
		exit (0);
	option->opt = opt;
	option->next = NULL;
	return (option);
}

t_argument	*ft_lstnew_arg(void *arg)
{
	t_argument	*argument;

	argument = malloc(sizeof(t_argument));
	if (!argument)
		exit (0);
	argument->arg = arg;
	argument->next = NULL;
	return (argument);
}

t_command	*ft_cmndnew(char *str)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		exit (0);
	command->cmnd = str;
	command->pipe = '\0';
	command->next = NULL;
	command->file = ft_lstnew_file(NULL);
	command->red = ft_lstnew_red(NULL);
	command->option = ft_lstnew_opt(NULL);
	command->argument = ft_lstnew_arg(NULL);
	return (command);
}
