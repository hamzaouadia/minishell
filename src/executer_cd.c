/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:30:01 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/16 15:57:50 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	int	i;

	i = 0;
	if (!g.environ)
		return (NULL);
	while (g.environ[i] != NULL)
	{
		if (strncmp(g.environ[i], str, strlen(str)) == 0)
			return (g.environ[i] + strlen(str));
		i++;
	}
	return (NULL);
}

void	ft_update_pwd(void)
{
	int	i;

	i = 0;
	while (g.environ[i] != NULL)
	{
		if (strncmp(g.environ[i], "PWD=", 4) == 0)
		{
			g.environ[i] = ft_strjoin(strdup("PWD="), g_glob.pwd);
			break ;
		}
		i++;
	}
}

void	ft_update_oldpwd(void)
{
	int	i;

	i = 0;
	while (g_glob.envp[i] != NULL)
	{
		if (strncmp(g_glob.envp[i], "OLDPWD=", 7) == 0)
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strjoin(strdup("OLDPWD="), g_glob.pwd);
			free(g_glob.pwd);
			return ;
		}
		i++;
	}
	free(g_glob.pwd);
}

char	*ft_cd_home(t_command *command)
{
    char    *path;
	path = ft_getenv("HOME=");
	if (path == NULL && command->argument->arg == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
	}
	else
		path = getenv("HOME");
	return (path);
}

int	ft_cd_cmmd(t_command *command)
{
	char	*path;

	path = NULL;
	g_glob.pwd = getcwd(NULL, 0);
	if (command->argument->arg == NULL || (command->argument->arg[0] == '~' && strlen(command->argument->arg) == 1))
		path = ft_cd_home(command);
	else
		path = command->argument->arg;
	if (path && chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, command->argument->arg, strlen(command->argument->arg));
		write(2, ": No such file or directory\n", 29);
	}
	path = getcwd(NULL, 0);
	if (path)
	{
		ft_update_pwd();
		free(path);
	}
	else
	{
		write(2, "err getcwd\n", 11);
		return (1);
	}
	return (0);
	
}

// int main(int ac , char **av)
// {
//     ft_cd_cmmd(av);
// }
