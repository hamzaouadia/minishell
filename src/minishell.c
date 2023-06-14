#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	char		*readl;
	t_command	*command;

	if (ac > 1)
		return (0);
	g.environ = env;
	while (1)
	{
		readl = readline("minishell:$");
		add_history(readl);
        readl = ft_expand_var(readl);
		command = ft_command(readl);
		ft_clean_command(command);
		while (command->next)
		{
			printf("command pipe      = %c\n", command->pipe);
			printf("command name      = %s\n", command->cmnd);
			while (command->option)
			{
				printf("command option    = %s\n", command->option->opt);
				command->option = command->option->next;
			}
			while (command->argument)
			{
				printf("command argument  = %s\n", command->argument->arg);
				command->argument = command->argument->next;
			}
			while (command->file)
			{
				printf("command file  = %s\n", command->file->fl);
				command->file = command->file->next;
			}
			while (command->red)
			{
				printf("command redi  = %s\n", command->red->rd);
				command->red = command->red->next;
			}
			printf("\n-------------------------------------------------\n");
			command = command->next;
		}
	}
	return (0);
}
