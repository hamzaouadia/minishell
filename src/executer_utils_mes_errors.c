#include "minishell.h"

void	print_errors_cd(int i)
{
	if (i == 0)
	{
		printf("minishell: No such file or directory\n");
	}
	else if (i == 1)
	{
		printf("minishell: cd: HOME not set\n");
		g_global.exit_code = 1;
		return ;
	}
}

int	utils_exit(int i)
{
	if (i == 0)
	{
		printf("exit\n");
		write(2, "minishell: exit: numeric argument required", 43);
		exit(255);
	}
	else if (i == 1)
	{
		printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 37);
		g_global.exit_code = 1;
		return (1);
	}
	else if (i == 2)
	{
		printf("exit\n");
		write(2, "minishell: exit: numeric argument required\n", 44);
		exit(255);
	}
	else if (i == 3)
	{
		printf("exit\n");
		exit(g_global.exit_code);
	}
	return (0);
}

int	print_errors_files(void)
{
	write(2, "bash: No such file or directory\n", 33);
	exit(127);
}

int	print_errors_files_2(void)
{
	write(2, "bash: No such file or directory\n", 33);
	g_global.exit_code = 1;
	return (1);
}

void	print_errors_exec(void)
{
	write(2, "bash: command not found\n", 25);
	g_global.exit_code = 127;
	exit(127);
}
