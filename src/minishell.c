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

void    ft_transfer_arg(t_argument *argument, t_red *red, t_commnd *cmd, int i)
{
	while (argument->arg)
	{
		cmd->cmd[i++] = strdup(argument->arg);
		free(argument->arg);
		argument = argument->next;
	}
	cmd->cmd[i] = NULL;
	i = 0;
	while (red->rd)
	{
		cmd->file[i++] = strdup(red->rd);
		cmd->file[i++] = strdup(red->fl);
		free(red->rd);
		free(red->fl);
		red = red->next;
	}
	cmd->file[i] = NULL;
}
int ft_transfer_command(t_command *command, int i, t_commnd *cmd)
{
    int			fl_len;
	int			arg_len;

	fl_len = 0;
	arg_len = 0;
    i = 0;
    arg_len = ft_count_arg(command->argument);
	if (command->cmnd)
		arg_len++;
	fl_len = ft_count_file(command->red);
	cmd->cmd = malloc(sizeof(char *) * (arg_len + 1));
	cmd->file = malloc(sizeof(char *) * (fl_len + 1));
	if (command->cmnd)
	{
		cmd->cmd[i++] = strdup(command->cmnd);
		free(command->cmnd);
	}
    return (i);
}

t_commnd	*ft_transfer_cmd(t_command *command)
{
	t_commnd	*cmd;
	t_commnd	*cmd_head;
	int			i;

	cmd = ft_new_cmd();
	cmd_head = cmd;
	while (command->next)
	{
       
		i = ft_transfer_command(command, i, cmd);
        ft_transfer_arg(command->argument, command->red, cmd, i);
		command = command->next;
		cmd->next = ft_new_cmd();
		cmd = cmd->next;
	}
	cmd = cmd_head;
	return (cmd);
}

void	ft_free_oldlist(t_command *command)
{
	t_command	*temp;
	t_red		*temp_red;
	t_argument	*temp_arg;

	while (command)
	{
		temp = command;
		while (command->argument)
		{
			temp_arg = command->argument;
			command->argument = command->argument->next;
			free(temp_arg);
		}
		while (command->red)
		{
			temp_red = command->red;
			command->red = command->red->next;
			free(temp_red);
		}
		command = command->next;
		free(temp);
	}
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

int	main(int ac, char **av, char **envp)
{
	char		*readl;
	t_command	*command;
	t_commnd	*cmd;
	t_env		*lst;
	t_all		*all;
	t_heredoc	*heredocc;

	(void)av;
	if (ac > 1)
		return (0);
	heredocc = NULL;
	lst = NULL;
	all = malloc(sizeof(t_all));
	all->heredocc = heredocc;
	all->fds = malloc(sizeof(t_fds));
	all->utils = malloc(sizeof(t_utils));
	copy_env(envp, &lst);
	all->lst = lst;
	while (1)
	{
		g_global.en = nodes_counter(&lst);
		readl = readline("minishell:$ ");
		add_history(readl);
		readl = ft_expand_var(readl, 0);
		command = ft_command(readl);
        if (command == NULL)
            continue;
		if (ft_clean_command(command) == -1)
            continue;
		cmd = ft_transfer_cmd(command);
		ft_free_oldlist(command);
		//printf ("%p\n", command);
		check_heredoc(cmd, &heredocc);
		if (ft_lstsize_cmd(cmd) == 1)
			exec_first_cmd(cmd, envp, &heredocc, all);
		else if (ft_lstsize_cmd(cmd) >= 2)
			exec_2_cmd(cmd, envp, &heredocc, all);
		while (heredocc)
		{
			close(heredocc->fd_pipe_heredoc);
			heredocc = heredocc->next;
		}
		ft_free_env(g_global.en);
		ft_free_cmd(cmd);
		heredocc = NULL;
	}
}
