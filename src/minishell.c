#include "../include/minishell.h"

t_file  *ft_lstnew_file(void *fl)
{
    t_file  *file;

    file = malloc(sizeof(t_file));
    if (!file)
        exit (0);
    file->fl = fl;
    file->next = NULL;
    return (file);
}

t_red  *ft_lstnew_red(void *rd)
{
    t_red  *red;

    red = malloc(sizeof(t_red));
    if (!red)
        exit (0);
    red->rd = rd;
    red->next = NULL;
    return (red);
}

t_option  *ft_lstnew_opt(void *opt)
{
    t_option  *option;

    option = malloc(sizeof(t_option));
    if (!option)
        exit (0);
    option->opt = opt;
    option->next = NULL;
    return (option);
}

t_argument  *ft_lstnew_arg(void *arg)
{
    t_argument  *argument;

    argument = malloc(sizeof(t_argument));
    if (!argument)
        exit (0);
    argument->arg = arg;
    argument->next = NULL;
    return (argument);
}

t_command   *ft_cmndnew(char    *str)
{
    t_command   *command;

    command = malloc(sizeof(t_command));
    if (!command)
    	exit (0);
    command->cmnd = str;
    command->pipe = '\0';
    command->next = NULL;
    command->file = ft_lstnew_file(NULL);
    command->red = ft_lstnew_red(NULL);
    command->option = ft_lstnew_opt(NULL);
    command->argument = ft_lstnew_arg(NULL);
    return (command);
}

int  ft_spchar_len(char *str, char d1, char d2)
{
    int  len;

    len = 0;
    if (!d1)
        d1 = d2;
    else if (!d2)
        d2 = d1;
    while (str[len] && (str[len] == d1 || str[len] == d2))
        len++;
    return (len);
}

int  ft_arg_len(char *str)
{
    int  len;
    char    q;

    len = -1;
    while (str[++len])
    {
        if (str[len] == '"' || str[len] == '\'')
        {
            q = str[len++];
            while (str[len] && str[len] != q)
                len++;
        }
        if (str[len] == ' ' || str[len] == '|' || str[len] == '>' || str[len] == '<')
            break;
    }
    return (len);    
}

int  ft_opt_len(char *str, char d)
{
    int  len;
    int     i;

    len = 1;
    i = 1;
    if (d == ' ')
        i = 0;
    if (str[0] != '-' || str[len] != 'n')
        return (0);
    while (str[len])
    {
        if (str[len] == '"' || str[len] == '\'')
            i++;
        if (str[len] == ' ' && d == ' ')
        {
            if (i % 2 == 0 || i == 0)
            {
                if (i != 0)
                    len++;
                break;
            }
        }
        if (str[len] == d && (str[len + 1] == ' ' || str[len + 1] == '|' || str[len + 1] == '>' || str[len + 1] == '<' || str[len + 1] == '\0'))
        {
            if (i % 2 == 0)
                break;
        }
        if (d == ' ' && (str[len] == '|' || str[len] == '>' || str[len] == '<'))
            return (len);
        if (str[len] != 'n' && str[len] != '"' && str[len] != '\'' && str[len] != '\'')
            return (0);
        len++;
    }
    if (d == '"' || d == '\'')
        len += 2;
    return(len);
}

int    command_option(char *str, int i, t_option *option)
{
    int len;
    int rec;
    int j;

    while (str[i] && str[i] != '|')
    {
        j = 0;
        while ((str[i] == ' ' || str[i] == '\t') && str[i])
            i++;
        rec = i;
        if (str[i] != '-' && str[i] != '"' && str[i] != '\'')
            return (rec);
        if (str[i] == '"' || str[i] == '\'')
            len = ft_opt_len(str + i + 1, str[i]);
        else
            len = ft_opt_len(str + i, str[i - 1]);
        if (len < 2)
            return (rec);
        option->opt = calloc((len + 1), sizeof(char));
        while (len > j)
            option->opt[j++] = str[i++];
        option->opt[j] = '\0';
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        option->next = ft_lstnew_opt(NULL);
        option = option->next;
    }
    return (i);
}

int    command_argument(char *str, int i, t_command *command)
{
    t_argument  *head_ar;
    t_red       *head_red;
    t_file      *head_fl;
    int len;
    int j;

    head_ar = command->argument;
    head_red = command->red;
    head_fl = command->file;
    while (str[i])
    {
        j = 0;
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '\0' || str[i] == '|')
            break ;
        if (str[i] == '<' || str[i] == '>')
        {
            len = ft_spchar_len(str + i, '<', '>');
            command->red->rd = calloc((len + 1), sizeof(char));
            while (len > j)
                command->red->rd[j++] = str[i++];
            command->red->rd[j] = '\0';
            command->red->next = ft_lstnew_red(NULL);
            command->red = command->red->next;
            while (str[i] == ' ' || str[i] == '\t')
                i++;
            if (str[i] && str[i] != '<' && str[i] != '>')
            {
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
                j = 0;
                len = ft_arg_len(str + i);
                command->file->fl = calloc((len + 1), sizeof(char));
                while (len > j)
                    command->file->fl[j++] = str[i++];
                command->file->fl[j] = '\0';
                command->file->next = ft_lstnew_file(NULL);
                command->file = command->file->next;
            }
            else
            {
                printf("-bash: syntax error near unexpected token\n");
                exit (0);
            }
            if (str[i] && str[i] != '<' && str[i] != '>' && command->cmnd == NULL)
            {
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
                j = 0;
                len = ft_arg_len(str + i);
                command->cmnd = calloc((len + 1), sizeof(char));
                while (len > j)
                    command->cmnd[j++] = str[i++];
            }
        }
        else
        {
            len = ft_arg_len(str + i);
            command->argument->arg = calloc((len + 1), sizeof(char));
            while (len > j)
                command->argument->arg[j++] = str[i++];
            command->argument->arg[j] = '\0';
            command->argument->next = ft_lstnew_arg(NULL);
            command->argument = command->argument->next;
        }
    }
    command->argument = head_ar;
    command->red = head_red;
    command->file = head_fl;
    return (i);
}

int    command_syntax(char *str, int i, t_command *command)
{
    int len;
    int j;
    
    j = 0;
    
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    len = ft_arg_len(str + i);
    if (len != 0)
    {
        command->cmnd = calloc((len + 1), sizeof(char));
        while (len > j)
            command->cmnd[j++] = str[i++];
        command->cmnd[j] = '\0';
    }
    i = command_option(str , i, command->option);
    i = command_argument(str, i, command);
    return (i);
}

t_command    *ft_command(char *str)
{
    t_command   *command;
    t_command   *head;
    int         i;

    command = ft_cmndnew(NULL);
    head = command;
    i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '|')
            command->pipe = str[i++];
        i = command_syntax(str, i, command);
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        command->next = ft_cmndnew(NULL);
        command = command->next;
    }
    
    return (head);
}

void    ft_quotes_syntax(char *str)
{
    int i;
    char q;
    
    i = 0;
    if (str == NULL)
        return ;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
         {
            q = str[i++];
            while (str[i] != q && str[i])
                i++;
            if (str[i] == '\0')
            {
                printf("-bash: syntax error\n");
                exit (0);
            }    
        }
        i++;
    }
}

void    ft_syntax_red(t_red *red)
{
    int i;

    while(red->next)
    {
        i = 0;
        if (red->rd == NULL)
            return ;
        i = strlen(red->rd);
        if (i > 2 || (red->rd[0] == '>' && red->rd[1] == '<'))
        {
            printf("-bash: syntax error near unexpected token\n");
            exit (0);
        }
        red = red->next;
    }
}

int    ft_quotes_len(char *str)
{
    int i;
    int quotes;
    char q;
    
    i = 0;
    quotes = 0;
    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
         {
            quotes++;
            q = str[i++];
            while (str[i] != q && str[i])
                i++;
        }
        i++;
    }
    return (quotes);
}

char    *ft_clean_quotes(char *arg)
{
    char    *new;
    int     i;
    int     j;
    char    q;
    new = malloc(sizeof(char) * (strlen(arg) - ft_quotes_len(arg) + 1));
    i = 0;
    j = 0;
    while (arg[i])
    {
        if (arg[i] == '"' || arg[i] == '\'')
         {
            q = arg[i++];
            while (arg[i] != q && arg[i])
                new[j++] = arg[i++];
        }
        else
            new[j++] = arg[i];
        i++;
    }
    new[j] = '\0';
    free(arg);
    return (new);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_check_var(char *arg, int i)
{
	char	*new;

	if (arg[i + 1] == '\0')
		return (arg);
	
	return(new);
}

void	ft_expand_var(t_argument	*argument)
{
	int 	i;
	int		q;

	while (argument)
	{
		i = -1;
		q = 0;
		while (argument->arg[++i])
		{
			if (argument->arg[i] == '\'')
				q++;
			if (argument->arg[i] == '$' && q % 2 == 0)
			{
				argument->arg = ft_check_var(argument->arg, i);
			}
		}
		argument = argument->next;
	}
	
}

void    ft_clean_command(t_command   *command)
{
    t_command   *head_cmd;

    head_cmd = command;
    if (command->pipe != '\0')
    {
        printf("%c\n", command->pipe);
        printf("-bash: syntax error\n");
        exit (0);
    }
    while (command->next)
    {
        ft_syntax_red(command->red);
		//ft_expand_var(command->argument);
        //command->cmnd = ft_clean_quotes(command->cmnd);
        command = command->next;
    }
    command = head_cmd;
}

int main(int ac, char **av, char **env)
{
	char		*readl;
	t_command	*command;

    if (ac > 1)
        return (0);
	global.environ = env;
    while (1)
    {
        readl = readline("minishell:$");
        add_history(readl);
        command = ft_command(readl);
        ft_clean_command(command);
        while (command->next)
        {
            printf("command pipe      = %c\n", command->pipe);
            printf("command name      = %s\n", command->cmnd);
            while (command->option)
            {
                printf("command option    = %s\n", command->option->opt);
                command->option = command->option->next;
            }
            while (command->argument)
            {
                printf("command argument  = %s\n", command->argument->arg);
                command->argument = command->argument->next;
            }
            while (command->file)
            {
                printf("command file  = %s\n", command->file->fl);
                command->file = command->file->next;
            }
            while (command->red)
            {
                printf("command redi  = %s\n", command->red->rd);
                command->red = command->red->next;
            }
            printf("\n-------------------------------------------------\n");
            command = command->next;
        }
    }
}
