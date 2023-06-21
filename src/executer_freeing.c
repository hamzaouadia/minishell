#include "minishell.h"

void	ft_free_lst(t_commnd *cmd)
{
	if (!cmd)
		return ;
	while (cmd)
	{
		ft_free_ddim(cmd->cmd);
		ft_free_ddim(cmd->file);
		cmd = cmd->next;
	}
}

void	ft_free_ddim(char **str)
{
	int i =0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}