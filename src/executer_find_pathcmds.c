#include "minishell.h"

char	*trouver_env(t_env *lst)
{
	t_env	*current;
	char	*path;

	path = NULL;
	g_global.env = lst;
	current = g_global.env;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			path = ft_strdup(current->value);
		current = current->next;
	}
	return (path);
}

char	**split_path(char *path)
{
	char	**path_split;

	path_split = NULL;
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	return (path_split);
}

char	*joindre_my_path(char **path_split)
{
	char	*str;
	int		i;

	i = 0;
	while (path_split && path_split[i])
	{
		str = path_split[i];
		path_split[i] = ft_strjoin(str, "/");
		free(str);
		if (!path_split)
			perror("ERROR");
		i++;
	}
	return (NULL);
}

char	*check_path(t_env *env, t_commnd *cmd)
{
	int		i;
	char	*commande;
	char	*str;
	char	**str2;

	i = 0;
	commande = cmd->cmd[0];
	if (access(commande, X_OK) == 0)
		return (commande);
	if (ft_strcmp(cmd->cmd[0], "./minishell") == 0 && !cmd->cmd[1])
		return (ft_strdup(""));
	str = trouver_env(env);
	str2 = split_path(str);
	joindre_my_path(str2);
	if (!str2)
		return (NULL);
	while (str2[i])
	{
		commande = ft_strjoin(str2[i], cmd->cmd[0]);
		if (access(commande, F_OK) == 0)
			return (commande);
		free(commande);
		i++;
	}
	return (NULL);
}
