#include "minishell.h"

void	ftPrintTowDim(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
	{
		printf("ptr not found!");
		return ;
	}
	while (ptr[i])
	{
		printf("ptr[%d] = |%s|\n", i, ptr[i]);
		i++;
	}
}

void	open_files(t_commnd *cmd, t_fds *fds, t_heredoc **heredocc)
{
	int	i;
	//dprintf(2, "-L<>%p\n", heredocc);

	fds->fd_in = -1;
	fds->fd_out = -1;
	i = 0;
	while (cmd->file && cmd->file[i])
	{
		if (ft_strcmp(cmd->file[i], "<") == 0 || ft_strcmp(cmd->file[i],
				">") == 0)
			open_files_helper(cmd, fds, i);
		else if (ft_strcmp(cmd->file[i], ">>") == 0)
		{
			fds->fd_out = open(cmd->file[i + 1], O_CREAT | O_APPEND | O_RDWR,
					0666);
			if (fds->fd_out == -1)
				print_errors_files();
		}
		else if (ft_strcmp(cmd->file[i], "<<") == 0)	
			fds->fd_in = (*heredocc)->fd_pipe_heredoc;
		i++;
	}
}

int	open_files_bu_helper(t_commnd *cmd, t_fds *fds, int i)
{
	
	if (ft_strcmp(cmd->file[i], "<") == 0)
	{
		fds->fd_in = open(cmd->file[i + 1], O_RDONLY, 0644);
		if (fds->fd_in == -1)
		{
			if (print_errors_files_2())
				return (1);
		}
	}
	else if (ft_strcmp(cmd->file[i], ">") == 0)
	{
		fds->fd_out = open(cmd->file[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0666);
		if (fds->fd_out == -1)
			print_errors_files_2();
	}
	return (0);
}

int	open_files_bu(t_commnd *cmd, t_fds *fds, t_heredoc **heredocc)
{
	int	i;

	initi_fds(fds);
	i = 0;
	while (cmd->file && cmd->file[i])
	{
		if (ft_strcmp(cmd->file[i], "<") == 0 || ft_strcmp(cmd->file[i],
				">") == 0)
		{
			if (open_files_bu_helper(cmd, fds, i))
				return (1);
		}
		else if (ft_strcmp(cmd->file[i], ">>") == 0)
		{
			fds->fd_out = open(cmd->file[i + 1], O_CREAT | O_APPEND | O_RDWR,
					0666);
			if (fds->fd_out == -1)
				if (open_files_bu_helper(cmd, fds, i))
					return (1);
		}
		else if (ft_strcmp(cmd->file[i], "<<") == 0)
			fds->fd_in = (*heredocc)->fd_pipe_heredoc;
		i++;
	}
	return (0);
}

void	exec_first_cmd(t_commnd *cmd, char **envp, t_heredoc **heredocc,
		t_all *all)
{
	//ftPrintTowDim(cmd->cmd);
	int	pid_fork;
	int	out;

	out = dup(1);
	pid_fork = 99;
	all->fds->fd_in = -1;
	all->fds->fd_out = -1;
	if (cmd->cmd == NULL)
		open_files_bu(cmd, all->fds, heredocc);
	if (check_builtins(cmd) == 1)
	{        
		if (open_files_bu(cmd, all->fds, heredocc) == 1)
			return ;
		if (all->fds->fd_out != -1)
			dup2(all->fds->fd_out, 1);
		(exec_builtins(cmd, all->lst), dup2(out, 1));
	}
	else if (check_builtins(cmd) == 0)
		pid_fork = fork();
	if (pid_fork == -1)
		print_errors_fork();
	if (pid_fork == 0)
	{
		
		exec_one_cmd(cmd, envp, all, heredocc);
	}
	else
		wait(NULL);
}

void	exec_2_cmd(t_commnd *cmd, char **envp, t_heredoc **heredocc1,
		t_all *all)
{
	initi_fds(all->fds);
	all->utils->stock_pipe = -1;
	if (cmd->cmd[0] == NULL)
		open_files_bu(cmd, all->fds, heredocc1);
	pipe(all->utils->fd_pipe);
	all->utils->pid_fork = fork();
	if (all->utils->pid_fork == -1)
		print_errors_fork();
	if (all->utils->pid_fork == 0)
	{
		exec_first_cmd_in_pipe(cmd, heredocc1, envp, all);
	}
	else
		helper1(cmd, envp, all, heredocc1);
}
