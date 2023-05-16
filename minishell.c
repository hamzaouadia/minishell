#include "minishell.h"

t_argument  *ft_lstnew(void *arg)
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
    size_t len;

    len = 0;
    while (str[len])
    {
        if (d == ' ' && str[len] == d)
            break;
        if ((str[len + 1] == ' ' || str[len + 1] == '|' || str[len + 1] == '>' || str[len + 1] == '<') && str[len] == d)
            break;
        if ((str[len] == '|' || str[len] == '>' || str[len] == '<') && d == ' ')
            break;
        len++;
    }
    if (d == '"' || d == '\'')
        len = len + 2;
    return (len);    
}

int    command_option(char *str, int i, t_option *option)
{
    int len;
    int rec;
    int j;

    while ((str[i] == ' ' || str[i] == '\t') && str[i])
        i++;
    rec = i;
    if (str[i] == '-')
    {
        j = 0;
        len = ft_arg_len(str + i, ' ');
        if (str[i + 1] != 'n' || len > 2)
            return (rec);
        option->opt = malloc(sizeof(char) * (len + 1));
        while (len > j)
        {
            option->opt[j++] = str[i];
            i = i + 1;
        }
        option->opt[j] = '\0';
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
        if (str[i] == '"')
            len = ft_arg_len(str + i + 1, '"');
        else if (str[i] == '\'')
            len = ft_arg_len(str + i + 1, '\'');
        else if (str[i] == '<' || str[i] == '>')
            len = ft_spchar_len(str + i, '<', '>');
        else
            len = ft_arg_len(str + i, ' ');
        argument->arg = malloc(sizeof(char) * (len + 1));
        while (len > j && str[i])
            argument->arg[j++] = str[i++];
        argument->arg[j] = '\0';
        argument->next = ft_lstnew(NULL);
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
    (*command)->cmnd = malloc(sizeof(char) * (len + 1));
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
            printf("command option   = %s\n", command->option->opt);
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
