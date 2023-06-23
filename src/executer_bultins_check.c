#include "minishell.h"

void	exec_builtins(t_commnd *cmd, t_env *lst)
{
	t_utils	*utils;

	utils = malloc(sizeof(t_utils));
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		my_cd(cmd, lst, utils);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		my_echo(cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		my_env(cmd, lst);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		my_exit(cmd);
	if (ft_strcmp(cmd->cmd[0], "export") == 0)
		my_export(cmd, lst, utils);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		my_pwd(0, lst);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		my_unset(cmd, &lst);
    free (utils);
}

int	check_builtins(t_commnd *cmd)
{
	if (cmd->cmd)
	{
		if (ft_strcmp(cmd->cmd[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "env") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			return (1);
		return (0);
	}
	return (-1);
}
