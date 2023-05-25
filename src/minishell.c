#include "../include/minishell.h"

t_option  *ft_lstnew_opt(void *opt)
{
    t_option  *list;

    list = malloc(sizeof(t_option));
    if (!list)
        exit (0);
    list->opt = opt;
    list->next = NULL;
    return (list);
}

t_argument  *ft_lstnew_arg(void *arg)
{
    t_argument  *list;

    list = malloc(sizeof(t_argument));
    if (!list)
        exit (0);
    list->arg = arg;
    list->next = NULL;
    return (list);
}

t_command   *ft_cmndnew(char    *str)
{
    t_command   *command;

    command = malloc(sizeof(t_command));
    command->option = malloc(sizeof(t_option));
    command->argument = malloc(sizeof(t_argument));
    if (!command || !command->option || !command->argument)
        exit (0);
    command->cmnd = str;
    command->pipe = '\0';
    command->next = NULL;
    command->option->opt = NULL;
    command->option->next = NULL;
    command->argument->arg = NULL;
    command->argument->next = NULL;
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

int    command_argument(char *str, int i, t_argument *argument)
{
    int len;
    int rec;
    int j;

    while (str[i])
    {
        j = 0;
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '\0' || str[i] == '|')
            break ;
        else if (str[i] == '<' || str[i] == '>')
            len = ft_spchar_len(str + i, '<', '>');
        else
            len = ft_arg_len(str + i);
        argument->arg = calloc((len + 1), sizeof(char));
        while (len > j)
            argument->arg[j++] = str[i++];
        argument->arg[j] = '\0';
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        argument->next = ft_lstnew_arg(NULL);
        argument = argument->next;
    }
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
    command->cmnd = calloc((len + 1), sizeof(char));
    while (len > j)
        command->cmnd[j++] = str[i++];
    command->cmnd[j] = '\0';
    i = command_option(str , i, command->option);
    i = command_argument(str, i, command->argument);
    return (i);
}

t_command    *ft_command(char *str)
{
    t_command   *line;
    t_command   *head;
    int         i;

    line = ft_cmndnew(NULL);
    head = line;
    i = 0;
    while (str[i])
    {
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '|')
            line->pipe = str[i++];
        i = command_syntax(str, i, line);
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        line->next = ft_cmndnew(NULL);
        line = line->next;
    }
    
    return (head);
}

void    ft_syntax_red(char *str)
{
    int i;
    char red;
    
    i = strlen(str);
    red = str[i];
    if (i > 2 || (str[0] == '>' && str[1] == '<'))
    {
        printf("-bash: syntax error near unexpected token\n");
        // exit (0);
    }
}

void    ft_quotes_syntax(char *str)
{
    int i;
    char q;
    
    i = 0;
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
                // exit (0);
            }    
        }
        i++;
    }
}

void    ft_syntax_arg(t_argument *argument)
{ 
    while(argument->next)
    {
        if (argument->arg[0] == '>' || argument->arg[0] == '<')
        {
            ft_syntax_red(argument->arg);
            if (argument->next)
            {
                if (argument->next->arg[0] == '>' || argument->next->arg[0] == '<')
                {
                    printf("-bash: syntax error near unexpected token %c\n", argument->arg[0]);
                    // exit (0);
                }
            }
        }
        ft_quotes_syntax(argument->arg);
        argument = argument->next;
    }
}

void    ft_syntax_error(t_command   *command)
{

    if (command->pipe != '\0')
    {
        printf("-bash: syntax error\n");
        // exit (0);
    }
    while (command->next)
    {
        ft_syntax_arg(command->argument);
        command = command->next;
    }
}

int main(int ac, char **av, char **env)
{
    char *readl;
    t_command *command;
    if (ac > 1)
        return 0;
    while (1)
    {
        readl = readline("minishell:$");
        add_history(readl);
        command = ft_command(readl);
        ft_syntax_error(command);
        while (command->next)
        {
            printf("command pipe     = %c\n", command->pipe);
            printf("command name     = %s\n", command->cmnd);
            while (command->option->next)
            {
                printf("command option   = %s\n", command->option->opt);
                command->option = command->option->next;
            }
            while (command->argument->next)
            {
                printf("command argument = %s\n", command->argument->arg);
                command->argument = command->argument->next;
            }
            printf("==================================================\n");
            command = command->next;
        }
    }
}
