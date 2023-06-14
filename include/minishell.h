#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>



typedef struct s_file
{
	char			*fl;
	struct s_file	*next;
}					t_file;

typedef struct s_red
{
	char			*rd;
	struct s_red	*next;
}					t_red;

typedef struct s_option
{
	char				*opt;
	struct s_option		*next;
}						t_option;

typedef struct s_argument
{
	char				*arg;
	struct s_argument	*next;
}						t_argument;

typedef struct s_command
{
	char				pipe;
	char				*cmnd;
	t_file				*file;
	t_red				*red;
	t_option			*option;
	t_argument			*argument;
	struct s_command	*next;
}						t_command;

typedef struct s_env
{
	int		exp_len;
	char	**environ;
}           t_env;

struct s_env g;

t_file		*ft_lstnew_file(void *fl);
t_red		*ft_lstnew_red(void *rd);
t_option	*ft_lstnew_opt(void *opt);
t_argument	*ft_lstnew_arg(void *arg);
t_command	*ft_cmndnew(char *str);

int			ft_quotes_len(char *str);
void		ft_quotes_syntax(char *str);
void		ft_syntax_red(t_red *red);
char		*ft_clean_quotes(char *arg);
void		ft_clean_command(t_command *command);

int			ft_spchar_len(char *str, char d1, char d2);
int			ft_arg_len(char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_exp_del(char c);
char		*ft_new_arg(char *arg, int i, char *en, int x);
char		*ft_check_var(char *arg, int i, int x);
char		*ft_expand_var(char *arg);


int			command_argument(char *str, int i, t_command *command);
int			command_syntax(char *str, int i, t_command *command);
t_command	*ft_command(char *str);

t_command	*ft_command(char *str);

#endif