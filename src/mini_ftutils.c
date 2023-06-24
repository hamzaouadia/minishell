#include "minishell.h"

t_commnd	*ft_new_cmd(void)
{
	t_commnd	*cmnd;

	cmnd = malloc(sizeof(t_commnd));
	if (!cmnd)
		exit (0);
	cmnd->cmd = NULL;
	cmnd->file = NULL;
	cmnd->next = NULL;
	return (cmnd);
}

int	ft_count_arg(t_argument *argument)
{
	int	i;

	i = 0;
	while (argument->arg)
	{
		argument = argument->next;
		i++;
	}
	return (i);
}

int	ft_count_file(t_red *red)
{
	int	i;

	i = 0;
	while (red->rd)
	{
		red = red->next;
		i += 2;
	}
	return (i);
}

void	ft_free_env(char **en)
{
	int	i;

	i = 0;
	while (en[i])
		free(en[i++]);
	free(en);
}

void	ft_free_cmd(t_commnd *cmd)
{
	int			i;
	t_commnd	*tmp;

	while (cmd)
	{
		i = 0;
		tmp = cmd;
		while (cmd->cmd && cmd->cmd[i])
			free(cmd->cmd[i++]);
		free(cmd->cmd);
		i = 0;
		while (cmd->file && cmd->file[i])
			free(cmd->file[i++]);
		free(cmd->file);
		cmd = cmd->next;
		free(tmp);
	}
	free(cmd);
}
