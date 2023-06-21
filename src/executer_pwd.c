#include "minishell.h"

char	*get_pwd(t_env *lst)
{
	t_env	*current;
	char	*pwd;

	current = lst;
	while (current)
	{
		if (ft_strncmp(current->key, "PWD", 3) == 0)
			pwd = ft_strdup(current->value);
		current = current->next;
	}
	return (pwd);
}

char	*my_pwd(int i, t_env *lst)
{
	char	cwd[1024];
	char	*pwd;
	char	*path;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (i != 1)
			printf("%s\n", cwd);
		g_global.exit_code = 0;
	}
	else
	{
		path = get_pwd(lst);
		if (i != 1)
			printf("%s\n", path);
		g_global.exit_code = 0;
	}
	pwd = ft_strdup(cwd);
	return (pwd);
}

char	*my_pwd2(int i, t_env *lst)
{
	char	cwd[1024];
	char	*pwd;
	char	*path;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (i != 1)
			printf("%s\n", cwd);
	}
	else
	{
		path = get_pwd(lst);
		if (i != 1)
			printf("%s\n", path);
	}
	pwd = ft_strdup(cwd);
	return (pwd);
}
