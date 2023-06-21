#include "minishell.h"

t_commnd    *ft_new_cmd(void)
{
    t_commnd    *cmnd;

    cmnd = malloc(sizeof(t_commnd));
    if (!cmnd)
        exit (0);
    cmnd->cmd = NULL;
    cmnd->file = NULL;
    cmnd->next = NULL;
    return (cmnd);
}

int ft_count_arg(t_argument *argument)
{
    int i;
    
    i = 0;
    while (argument->arg)
    {
        argument = argument->next;
        i++;
    }
    return (i);
}

int ft_count_file(t_red *red)
{
    int i;
    
    i = 0;
    while (red->rd)
    {
        red = red->next;
        i += 2;
    }
    return (i);
}

t_commnd    *ft_transfer_cmd(t_command  *command)
{
    t_commnd    *cmd;
    t_commnd    *cmd_head;
    int fl_len;
    int arg_len;
    int i;

    fl_len  = 0;
    arg_len  = 0;
    cmd = ft_new_cmd();
    cmd_head = cmd;
    while (command->next)
    {
        i = 0;
        arg_len = ft_count_arg(command->argument);
        if (command->cmnd)
            arg_len++;
        fl_len = ft_count_file(command->red);
        cmd->cmd = malloc(sizeof(char *) * (arg_len + 1));
        cmd->file = malloc(sizeof(char *) * (fl_len + 1));
        if (command->cmnd)
            cmd->cmd[i++] = strdup(command->cmnd);
        while (command->argument->arg)
        {
            cmd->cmd[i++] =  strdup(command->argument->arg); 
            command->argument = command->argument->next;
        }
        cmd->cmd[i] = NULL;
        i = 0;
        while (command->red->rd)
        {
            printf ("|%s|\n", command->red->rd);
            cmd->file[i++] =  strdup(command->red->rd); 
            cmd->file[i++] =  strdup(command->red->fl); 
            command->red = command->red->next;
        }
        cmd->file[i] = NULL;
        command = command->next;
        cmd->next = ft_new_cmd();
        cmd = cmd->next;
    }
    cmd = cmd_head;
    return (cmd);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	char		*readl;
	t_command	*command;
	t_commnd	*cmd;
	t_commnd	*cmd_head;


    t_env		*lst;
	char		**ret;
	t_all       *all;
	t_fds		*fds;
	t_heredoc	*heredocc;
	t_utils     *utils;

	if (ac > 1)
		return (0);

	heredocc = NULL;
    lst = NULL;
	ret = NULL;
    all =   malloc(sizeof(t_all));
	utils = malloc(sizeof(t_utils));
	fds = malloc(sizeof(t_fds));
    all->heredocc = heredocc; 
	all->fds = fds; 
	all->utils = utils;
	copy_env(envp, &lst);
	g_global.en = nodes_counter(&lst);
	all->lst = lst;

    while (1)
	{
		readl = readline("minishell:$ ");
		add_history(readl);
        readl = ft_expand_var(readl);
		command = ft_command(readl);
		ft_clean_command(command);
        cmd = ft_transfer_cmd(command);
        cmd_head = cmd;
        check_heredoc(cmd, &heredocc);
		if (ft_lstsize_cmd(cmd) == 1)
			exec_first_cmd(cmd, envp, &heredocc, all);
		else if (ft_lstsize_cmd(cmd) >= 2)
			exec_2_cmd(cmd, envp, &heredocc,all);
		while (heredocc)
		{
			close(heredocc->fd_pipe_heredoc);
			heredocc = heredocc->next;
		}
			
		heredocc = NULL;
    }
}
