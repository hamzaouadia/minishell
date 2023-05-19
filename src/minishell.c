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

size_t  ft_spchar_len(char *str, char d1, char d2)
{
    size_t  len;

    len = 0;
    if (!d1)
        d1 = d2;
    else if (!d2)
        d2 = d1;
    while (str[len] && (str[len] == d1 || str[len] == d2))
    {
        if (str[len] == '|')
            break;
        len++;
    }
    return (len);
}

size_t  ft_arg_len(char *str, char d)
{
    size_t  len;
    int     i;

    len = 0;
    i = 1;
    if (d == ' ')
        i = 0;
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
            break;
        len++;
    }
    if (d == '"' || d == '\'')
        len += 2;
    return (len);    
}

size_t  ft_opt_len(char *str, char d)
{
    size_t  len;
    int     i;

    len = 1;
    i = 1;
    if (d == ' ')
        i = 0;
    if (str[0] != '-')
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
        if (str[len] != 'n')
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
        if (len == 0)
            return (rec);
        option->opt = calloc((len + 1), sizeof(char));
        while (len > j)
        {
            option->opt[j++] = str[i];
            i = i + 1;
        }
        option->opt[j] = '\0';
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

    while (str[i] && str[i] != '|')
    {
        j = 0;
        while (str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i] == '\0' || str[i] == '|')
            break ;
        if (str[i] == '"' || str[i] == '\'')
            len = ft_arg_len(str + i + 1, str[i]);
        else if (str[i] == '<' || str[i] == '>')
            len = ft_spchar_len(str + i, '<', '>');
        else
            len = ft_arg_len(str + i, ' ');
        argument->arg = calloc((len + 1), sizeof(char));
        while (len > j && str[i])
            argument->arg[j++] = str[i++];
        argument->arg[j] = '\0';
        argument->next = ft_lstnew_arg(NULL);
        argument = argument->next;
    }
    return (i);
}

int    command_syntax(char *str, int i, t_command **command)
{
    int len;
    int j;
    
    j = 0;
    
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    len = ft_arg_len(str + i, ' ');
    (*command)->cmnd = calloc((len + 1), sizeof(char));
    while (len > j)
        (*command)->cmnd[j++] = str[i++];
    (*command)->cmnd[j] = '\0';
    i = command_option(str , i, (*command)->option);
    i = command_argument(str, i, (*command)->argument);
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
        i = command_syntax(str, i, &line);
        line->next = ft_cmndnew(NULL);
        line = line->next;
    }
    
    return (head);
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
