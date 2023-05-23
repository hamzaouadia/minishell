#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_option
{
    char                *opt;
    struct  s_option    *next;
}   t_option;

typedef struct s_argument
{
    char                *arg;
    struct  s_argument    *next;
}   t_argument;

typedef struct  s_command
{
    char        pipe;
    char        *cmnd;
    t_option    *option;
    t_argument  *argument;
    struct  s_command   *next;
}   t_command;

t_command    *ft_command(char *str);

#endif