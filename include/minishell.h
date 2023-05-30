#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

struct s_global
{
	int		i;
	char	**environ;
}			global;

typedef struct s_file
{
    char            *fl;
    struct  s_file  *next;
}   t_file;

typedef struct s_red
{
    char            *rd;
    struct  s_red   *next;
}   t_red;

typedef struct s_option
{
    char                *opt;
    struct  s_option    *next;
}   t_option;

typedef struct s_argument
{
    char                *arg;
    struct  s_argument  *next;
}   t_argument;

typedef struct  s_command
{
    char        pipe;
    char        *cmnd;
    t_file      *file;
    t_red       *red;
    t_option    *option;
    t_argument  *argument;
    struct  s_command   *next;
}   t_command;

t_command    *ft_command(char *str);

#endif