/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouassa <aaouassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:51:25 by aaouassa          #+#    #+#             */
/*   Updated: 2023/06/16 16:51:55 by aaouassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_option(char *args)
{
	int	i;

	i = 2;
	if (args && (args[0] == '-' && args[1] == 'n'))
	{
		while (args[i] == 'n')
			i++;
		if (args[i] == '\0')
			return (1);
	}
    return (0);
}

int	ft_echo_cmmd(t_command *command)
{
	int	n;

	n = 0;
    n = ft_check_option(command->argument->arg);
    if (n == 1)
        command->argument = command->argument->next;
	while (command->argument->arg)
	{
        
		printf("%s",command->argument->arg);
		if (command->argument->next->arg)
            printf(" ");
		command->argument = command->argument->next;
	}
    if (n == 0)
	    printf("\n");
    return(0);
}

// t_data	*init_data(char **envp)
// {
// 	t_data	*data;
// 	int		i;

// 	i = 0;
// 	data = malloc(sizeof(t_data));
// 	data->args = NULL;
// 	data->error = 0;
// 	data->inf = NULL;
// 	data->infiles = NULL;
// 	data->n_infiles = 0;
// 	data->outfiles = NULL;
// 	data->append = NULL;
// 	data->hd = NULL;
// 	data->if_hd = 0;
// 	if (g_glob.g_env == 0)
// 	{
// 		g_glob.envp = create_envp(envp);
// 		g_glob.g_env = 1;
// 	}
// 	if (g_glob.g_exp == 0)
// 	{
// 		g_glob.exp = creat_export(envp);
// 		g_glob.g_exp = 1;
// 	}
// 	return (data);
// }

// int	ft_bulitins(t_list *exec)
// {
// 	if (!exec)
// 		return (0);
// 	if (!((t_data *)exec->content)->args)
// 		return (0);
// 	if (!strncmp(((t_data *)exec->content)->args[0], "cd", 3))
// 		return (1);
// 	// if (!strncmp(((t_data *)exec->content)->args[0], "pwd", 4))
// 	// 	return (1);
// 	// else if (!strncmp(((t_data *)exec->content)->args[0], "echo", 5))
// 	// 	return (1);
// 	// else if (!strncmp(((t_data *)exec->content)->args[0], "env", 4))
// 	// 	return (1);
// 	// else if (!strncmp(((t_data *)exec->content)->args[0], "export", 7))
// 	// 	return (1);
// 	// else if (!strncmp(((t_data *)exec->content)->args[0], "unset", 6))
// 	// 	return (1);
// 	// else if (!strncmp(((t_data *)exec->content)->args[0], "exit", 6))
// 	// 	return (1);
// 	return (0);
// }

int	ft_pwd_cmmd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		s = ft_getenv("PWD=");
		if (s != NULL)
			printf("%s\n", s);
		else
			printf("pwd is unseted\n");
	}
	else
	{
		printf("%s\n", s);
		free(s);
	}
	return (0);
}

int	ft_env_cmmd(void)
{
	int	i;

	i = -1;
	// if (g_glob.env == 1)
	// {
	// 	write(2, "minishell: env: No such file or directory\n", 42);
	// 	return (1);
	// }
	// else
		while (g.environ[++i])
			printf("%s\n", g.environ[i]);
	return (0);
}

int	ft_count_args(t_argument *argument)
{
	int	i;

	if (argument == NULL)
		return (0);
	i = 0;
	while (argument->arg)
    {
        argument = argument->next;
		i++;
    }
	return (i + 1);
}

void	ft_numeric(char *arg)
{
	//int	i;
	int	j;

	//i = 1;
	j = 0;
    if (!arg)
        return ;
	// while (arg[i] != NULL)
	// {
		while (arg[j])
		{
			if ((arg[0] == '-' || arg[0] == '+') && arg[1] == '0'
			&& !atoi(&arg[1]))
				(printf("exit\n"), exit(0));
			if (arg[j] != '0' && !atoi(&arg[j]))
			{
				write(2, "minishell: exit: ", 17);
				write(2, arg, strlen(arg));
				write(2, ": numeric argument required\n", 28);
			}
			j++;
		}
	// 	i++;
	// }
}

int	ft_exit_cmmd(t_command *command)
{
	long long	len;

	len = ft_count_args(command->argument);
	if (!command->argument->arg)
		(printf("exit\n"));
	ft_numeric(command->argument->arg);
	write(2, &len, 4);
	if (len > 3)
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
	else if (len == 3)
	{
		len = atoi(command->argument->arg);
		if (command->argument->arg[0] != '-' && len < 0)
		{
			write(2, "minishell: exit: ", 17);
			write(2, command->argument->arg, strlen(command->argument->arg));
			write(2, ": numeric argument required\n", 28);
			exit(255);
		}
		else
			(printf("exit\n"), exit(atoi(command->argument->arg)));
	}
	return (1);
}

int	ft_get_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (i);
}

char	*ft_get_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * ft_get_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < ft_get_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

int	ft_big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
	{
		write(fd, s, 1);
		s++;
	}
}

void	ft_error_export(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	//ft_putendl_fd("': not a valid identifier", 2);
	// g_glob.g_exit_status = 1;
}

int ft_count_env_arg(char **strs)
{
    int i;

    i = 0;
    while (strs[i] != NULL)
        i++;
    return (i);
}

char	**add_env(char **strs, char *arg)
{
	char	**args;
	int		i;

	if (!strs[0])
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = strdup(arg);
		args[1] = NULL;
		free(strs);
		return (args);
	}
	args = (char **)malloc(sizeof(char *) * (ft_count_env_arg(strs) + 1));
        printf("*********%d**************\n",(ft_count_env_arg(strs)));
	i = -1;
	while (strs[++i])
	{
		args[i] = strdup(strs[i]);
		free(strs[i]);
	}
	args[i] = strdup(arg);
	free(strs);
	args[i + 1] = NULL;
	return (args);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	ft_checkin_error(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
		return (1);
	i = 1;
	while (arg[i])
	{
		if (!ft_acceptable(arg[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_new_line(char *name, char *value)
{
	char	*tmp;

	tmp = calloc(1, sizeof(char));
	tmp = ft_strjoin(tmp, "declare -x ");
	tmp = ft_strjoin(tmp, name);
	if (value)
	{
		tmp = ft_strjoin(tmp, "=\"");
		tmp = ft_strjoin(tmp, value);
		tmp = ft_strjoin(tmp, "\"");
	}
	return (tmp);
}

int	ft_exist(char *name)
{
	int		i;
	char	*tmp;

	tmp = ft_new_line(name, NULL);
	i = -1;
	while (g.environ[++i])
	{
		if (strncmp(g.environ[i], tmp, \
				ft_big_len(ft_get_index(g.environ[i], '='), strlen(tmp))) == 0)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}

char	*g_v_n(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * ft_get_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < ft_get_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

char	*ft_join_tmp(char *tmp, char *name, char *value)
{
	tmp = calloc(1, sizeof(char));
	tmp = ft_strjoin(tmp, name);
	tmp = ft_strjoin(tmp, "=");
	tmp = ft_strjoin(tmp, value);
	return (tmp);
}

void	ft_set_expo(char *name, char *value, int exist)
{
	int		j;
	char	*tmp;

	j = -1;
	tmp = ft_new_line(name, value);
	if (exist)
	{
		while (value && g.environ[++j])
		{
			if (!strncmp(g.environ[j], tmp,
					ft_big_len(ft_get_index(g.environ[j], '='), ft_get_index(tmp, '='))))
			{
				free(g.environ[j]);
				g.environ[j] = strdup(tmp);
				free(tmp);
				return ;
			}
		}
	}
	else
		g.environ = add_env(g.environ, tmp);
	free(tmp);
}

void	ft_set_env(char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	tmp = NULL;
	if (!value)
		return ;
	tmp = ft_join_tmp(tmp, name, value);
	while (g.environ[++i])
	{
		tmp2 = g_v_n(g.environ[i]);
		if (!strncmp(tmp2, name, ft_big_len(strlen(tmp2), strlen(name))))
		{
			free(g.environ[i]);
			g.environ[i] = strdup(tmp);
			free(tmp);
			free(tmp2);
			return ;
		}
		free(tmp2);
	}
	g.environ = add_env(g.environ, tmp);
	free(tmp);
}

void	ft_new_env(t_argument *argument)
{
	char	*nom;
	char	*val;

	while (argument->arg)
	{
		val = NULL;
		nom = ft_get_name(argument->arg);
		if ((!nom || !nom[0]) || ft_checkin_error(nom))
		{
			(ft_error_export(argument->arg), free(nom));
			continue ;
		}
		if (strchr(argument->arg, '='))
			val = strdup(argument->arg + ft_get_index(argument->arg, '=') + 1);
		if (ft_exist(nom) != -1)
			(ft_set_env(nom, val), ft_set_expo(nom, val, 1));
		else
			(ft_set_env(nom, val), ft_set_expo(nom, val, 0));
		free(nom);
		free(val);
	}
}

int	ft_export_cmmd(t_command *command)
{
	int		len;
	int		i;

	i = -1;
	len = ft_count_args(command->argument);
	if (len == 0)
		while (g.environ[++i])
			printf("%s\n", g.environ[i]);
	else
		ft_new_env(command->argument);
	return (0);
}

int	ft_execute_bulitins(t_command *exec, int mode)
{
	if (exec->cmnd && !strncmp(exec->cmnd, "cd", 3))
		return (ft_cd_cmmd(exec));
	else if (exec->cmnd && !strncmp(exec->cmnd, "pwd", 4))
	 	return (ft_pwd_cmmd());
	else if (exec->cmnd && !strncmp(exec->cmnd, "echo", 5))
		return (ft_echo_cmmd(exec));
	else if (exec->cmnd && !strncmp(exec->cmnd, "env", 4))
	 	return (ft_env_cmmd());
	else if (exec->cmnd && !strncmp(exec->cmnd, "export", 7))
	  	return (ft_export_cmmd(exec));
	// else if (!strncmp(((t_data *)exec->content)->args[0], "unset", 6))
	// 	return (ft_unset_cmmd(((t_data *)exec->content)->args));
	else if (exec->cmnd && !strncmp(exec->cmnd, "exit", 6))
	 	return (ft_exit_cmmd(exec));
	if (mode == 0)
		return (0);
	return (1);
}