#include "minishell.h"

void	my_env(t_commnd *cmd, t_env *lst)
{
	int		i;
	int		x;
	t_env	*current;

	i = 0;
	current = lst;
	x = count_args(cmd->cmd);
    printf ("%s\n", current->key);
	if (x >= 2)
	{
		printf("env: %s: No such file or directory\n",
			cmd->cmd[1]);
		g_global.exit_code = 127;
		return ;
	}
	while (current)
	{
		if (current->value)
			printf("%s\n", ft_strjoin(ft_strjoin(current->key, "="),
					current->value));
		current = current->next;
		i++;
	}
	g_global.exit_code = 0;
}
