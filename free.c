#include "include/minishell.h"

int main()
{

    t_argument *arg;
    t_argument *save;

    arg = malloc(sizeof(t_argument));
    arg->arg = malloc(sizeof(char) * 2);
    arg->arg[0] = '1';
    arg->arg[1] = '\0';

    arg->next = malloc(sizeof(t_argument));
    arg->next->arg = malloc(sizeof(char) * 2);
    arg->next->arg[0] = '2';
    arg->next->arg[1] = '\0';
    save = arg;
    arg = arg->next;
    free (save->arg);
    free (save);
    printf("%s\n", arg->arg);
    free (arg->arg);
    free (arg);
}
