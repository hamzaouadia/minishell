#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/errno.h>

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

typedef struct s_argument
{
	char				*arg;
	struct s_argument	*next;
}						t_argument;

typedef struct s_env
{
	int		exp_len;
	char	**environ;
}           t_env;

struct s_env g;

typedef struct s_command
{
	char				pipe;
	char				*cmnd;
	t_file				*file;
	t_red				*red;
	t_argument			*argument;
	struct s_command	*next;
}						t_command;

/*---------------------------------------------*/
typedef struct s_glob
{
	int		fdout;
	int		fd_in;
	int		g_exit_status;
	int		g_env;
	int		g_exp;
	char	**envp;
	char	**exp;
	char	*pwd;
	int		env;
	int 	pid;
	int		copy_fd;
	int		tmpin;
	int 	tmpout;
	int		g_child;
	int		last;
	int		j;
	
}				t_glob;
t_glob			g_glob;


typedef struct s_data
{
	char	**args;
	int		error;
	int		if_hd;
	char	*inf;
	int		*infiles;
	int		n_infiles;
	char	**outfiles;
	char	**append;
	char	**hd;
	int		end[2];
	char	**envp;
}				t_data;
/*---------------------------------------------*/

t_file		*ft_lstnew_file(void *fl);
t_red		*ft_lstnew_red(void *rd);
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
int	        ft_exp_check(char c);
char		*ft_new_arg(char *arg, int i, char *en, int x);
char		*ft_check_var(char *arg, int i, int x);
char		*ft_expand_var(char *arg);


int			command_argument(char *str, int i, t_command *command);
int			command_syntax(char *str, int i, t_command *command);
t_command	*ft_command(char *str);
t_command	*ft_command(char *str);

/*----------------------------------------------------*/


char	*ft_cd_home(t_command *command);
int	    ft_cd_cmmd(t_command *command);
char	    *ft_getenv(char *str);
char	    *strdup(const char *s1);
char	    *ft_strjoin(char	const *s1, char	const *s2);
int		strncmp(const char *s1, const char *s2, size_t n);
size_t	strlen(const	char *s);


int		ft_execute_bulitins(t_command *exec, int mode);

#endif