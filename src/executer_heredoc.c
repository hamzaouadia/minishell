#include "minishell.h"

int	count_heredoc(t_commnd *cmd)
{
    t_commnd *head;

    head = cmd;
	int	counter;
	int	i;

	counter = 0;
	while (cmd->next)
	{
		i = 0;
		while (cmd->file && cmd->file[i])
		{
			if (ft_strcmp(cmd->file[i], "<<") == 0)
				counter++;
			i++;
		}
		cmd = cmd->next;
	}
    cmd = head;
	return (counter);
}

int	check_find_herdoc(t_commnd **cmd, int i)
{
	t_commnd	*tmp;

	tmp = *cmd;
	while (tmp->file && tmp->file[i])
	{
		if (ft_strcmp(tmp->file[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	read_heredoc(char *delimit, t_heredoc **heredocc, int i, t_commnd *cmd)
{
	char	*heredoc;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		heredoc = readline("< ");
		if (ft_strcmp(heredoc, delimit) == 0)
			break ;
		write(fd[1], heredoc, ft_strlen(heredoc));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	if (check_find_herdoc(&cmd, i))
		close(fd[0]);
	else
		ft_lstadd_back_heredoc(heredocc, ft_lstnew_heredoc(fd[0]));
}

void	check_heredoc(t_commnd *cmd, t_heredoc **heredoc)
{
    t_commnd *head;
	int		i;
	int		num_heredoc;
	char	*delimit;

    head = cmd;
	i = 0;
	num_heredoc = count_heredoc(cmd);
	delimit = ft_calloc(1, 1);
	if (num_heredoc > 16)
		print_erros_heredoc();
	while (cmd->next)
	{
		i = 0;
		while (cmd->file[i])
		{
			if (ft_strcmp(cmd->file[i], "<<") == 0)
			{
				delimit = cmd->file[i + 1];
				read_heredoc(delimit, heredoc, i + 1, cmd);
			}
			i++;
		}
		cmd = cmd->next;
	}
    cmd = head;
}

// khasni ndir tableau de deux dimensions kanhet fih fds dyal pipes ,
//kansavu fih 0 u 1 u kanbqa ntcheki ela wach kayn heredoc muraha
//la kan kanbqa nsed 0 dyalu u 1 (waqila) ila kan murah null yaeni 
//pipe ula makayn tahaja rah kansavi [0].//
// qbl mn kula heredoc khasni nopeni pipe u 
//nsed fd_pie[0] dyalu u mn bead man hel herdoce ngulih ikteb fdfd_pipe[1]
// mn bead ansavi akhir fd[0] dyal pipe bach nqrra menu lcommande

// tableau deux dimensions fi integr anbqa nzid bih
// fonction katcheki wch li muraha herdoc la kan kansedu 0
// nalouer bnombre dyal nodes li endi