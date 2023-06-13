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
    int  ex;
    char    q;

    len = -1;
    ex = 0;
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
    return (len + ex);    
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	join = (char *)malloc(sizeof(char) * (i + j) + 1);
	if (!join)
		return (NULL);
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (join - i - j);
}

int     ft_exp_del(char c)
{
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (0);
    return (1);
}

char    *ft_new_arg(char *arg, int i, char *en)
{
    char    *new;
    char    *exp;
    int     len;
    int     j;
    int     k;

    len = 0;
    j = 0;
    k = 0;
    while (en[len])
        len++;
    global.exp_len = len;
    exp = malloc(sizeof(char) * (len + i + 1));
    len = 0;
    while (len < i)
        exp[j++] = arg[len++];
    len++;
    while (arg[len] && ft_exp_del(arg[len]) == 0)
        len++;
    while (en[k])
        exp[j++] = en[k++];
    exp[j] = '\0';
    new = ft_strjoin(exp, arg + len);
    free(arg);
    free(exp);
    return (new);
}

char	*ft_check_var(char *arg, int i)
{
    int     j;
    int     k;
    int     e;

	e = 0;
    while (global.environ[e])
    {
        k = 0;
        j = i + 1;
        while (arg[j] == global.environ[e][k])
        {
            j++;
            k++;
        }
        if (ft_exp_del(arg[j]) == 1 && global.environ[e][k] == '=')
        {
            arg = ft_new_arg(arg, i, global.environ[e] + k + 1);
            return(arg);
        }
        e++;
    }
	
	return(arg);
}

char	*ft_expand_var(char *arg)
{
	int 	i;
	int		j;

    i = 0;
	while (arg[i])
	{
        if (arg[i] == '"')
        {
            i++;
            while (arg[i] && arg[i] != '"')
            {
                if (arg[i] == '$')
                {
                    arg = ft_check_var(arg, i);
                    i = i + global.exp_len;
                }
                else
                    i++;
            }
        }
        if (arg[i] == '\'')
        {
            i++;
            while (arg[i] && arg[i] != '\'')
                i++;
        }
        if (arg[i] == '$')
        {
            arg = ft_check_var(arg, i);
            i = i + global.exp_len;
        }
        else
            i++;
	}
    return (arg);
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
            if (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '|')
            {
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
                j = 0;
                len = ft_arg_len(str + i);
                command->file->fl = calloc((len + 1), sizeof(char));
                while (len > j)
                    command->file->fl[j++] = str[i++];
                command->file->fl[j] = '\0';
                command->file->fl = ft_expand_var(command->file->fl);
                command->file->next = ft_lstnew_file(NULL);
                command->file = command->file->next;
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
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
                while (str[i] == ' ' || str[i] == '\t')
                    i++;
            }
        }
        else
        {
            len = ft_arg_len(str + i);
            command->argument->arg = calloc((len + 1), sizeof(char));
            while (len > j)
                command->argument->arg[j++] = str[i++];
            command->argument->arg[j] = '\0';
            command->argument->arg = ft_expand_var(command->argument->arg);
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

void    ft_clean_command(t_command   *command)
{
    t_command   *head_cmd;
    t_argument  *head_arg;
    t_file      *head_file;

    head_cmd = command;
    head_arg = command->argument;
    head_file = command->file;
    if (command->pipe != '\0')
    {
        printf("%c\n", command->pipe);
        printf("-bash: syntax error\n");
        exit (0);
    }
    while (command->next)
    {
        ft_syntax_red(command->red);
        command->cmnd = ft_clean_quotes(command->cmnd);
        while (command->argument->next)
        {
            command->argument->arg = ft_clean_quotes(command->argument->arg);
            command->argument = command->argument->next;
        }
        while (command->file->next)
        {
            command->file->fl = ft_clean_quotes(command->file->fl);
            command->file = command->file->next;
        }
        command = command->next;
    }
    command = head_cmd;
    command->argument = head_arg;
    command->file = head_file;
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
