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

# include <termios.h>
# include <errno.h>

typedef struct s_red
{
	char			*rd;
	char			*fl;
	struct s_red	*next;
}					t_red;

typedef struct s_argument
{
	char				*arg;
	struct s_argument	*next;
}						t_argument;

typedef struct s_command
{
	char				pipe;
	char				*cmnd;
	t_red				*red;
	t_argument			*argument;
	struct s_command	*next;
}						t_command;

/*---------------------------------------------*/

typedef struct s_fds
{
	int					fd_in;
	int					fd_out;
}						t_fds;

typedef struct env
{
	char				*key;
	char				*value;
	struct env			*next;
}						t_env;

typedef struct utils
{
	char				*old;
	char				*my_home;
	char				*new;
	int					c;
	int					i;
	int					flag;
	int					flag2;
	char				*str;
	int					fd_pipe[2];
	int					stock_pipe;
	int					pid_fork;
	t_env				*current;
}						t_utils;

typedef struct s_global
{
	int				exit_code;
	char			*check;
	t_env			*env;
	int				exp_len;
}					t_global;

t_global				g_global;

typedef struct pipe
{
	int					fd_pipe[2];
}						t_pipes;

// for envirnmt


typedef struct s_heredoc
{
	int					fd_pipe_heredoc;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_all
{
	t_env				*lst;
	t_utils				*utils;
	t_fds				*fds;
	t_heredoc			*heredocc;
}						t_all;

typedef struct s_commnd
{
	char				**cmd;
	char				**file;
	struct s_commnd		*next;
}						t_commnd;

/*---------------------------------------------*/

t_red		*ft_lstnew_red(void *rd);
t_argument	*ft_lstnew_arg(void *arg);
t_command	*ft_cmndnew(char *str);

int			ft_quotes_len(char *str);
int			ft_quotes_syntax(char *str);
int			ft_syntax_red(t_red *red);
char		*ft_clean_quotes(char *arg);
int			ft_clean_command(t_command *command);

int			ft_spchar_len(char *str, char d1, char d2);
int			ft_arg_len(char *str);
int			ft_exp_del(char c);
int			ft_exp_check(char c);
char		*ft_new_arg(char *arg, int i, char *en, int x);
char		*ft_check_var(char *arg, int i, int x);
char		*ft_expand_var(char *arg, int ex);

int			command_argument(char *str, int i, t_command *command);
int			command_syntax(char *str, int i, t_command *command);
t_command	*ft_command(char *str);
t_command	*ft_command(char *str);
char		**nodes_counter(t_env **env);
char		*ft_itoa(int n);
int			ft_count_red(char *en);
void		ft_free_oldlist(t_command *command);
void		ft_free_herdocc(t_heredoc **heredocc);

int			ft_white_spaces(char *str, int i);
int			ft_file_condition(char *str, int i, t_command *command);
int			ft_cmnd_after_red(char *str, int i, t_command *command);
int			ft_arg_len(char *str);


int			ft_spchar_len(char *str, char d1, char d2);
void		put_str(char *string, long long int nb, int size);
int			string_size(long long int nb);
int			ft_exp_check(char c);
int			ft_exp_del(char c);
int			ft_count_red(char *en);
void		ft_protect_var(char *en, int len, int x);
char		*ft_remove_and_excode(char *arg, int i);
int			ft_expand_condition(char *arg, int i);
int			ft_singl_qexp(char *arg, int i, int ex);
char		*ft_double_qexp(char *arg, int *i);
char		*ft_expand_var(char *arg, int ex);
int			ft_env_len(t_env **env);
char		*ft_remove_var(char *arg, int i);

void		ft_free_cmd(t_commnd *cmd);
void		ft_free_env(char **en);
int			ft_count_file(t_red *red);
int			ft_count_arg(t_argument *argument);
t_commnd	*ft_new_cmd(void);

/*      Exec Part            */
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(char *str);
char		*my_pwd(int i, t_env *lst);
int			ft_strlen(char *str);
int			count_n(char *str);
int			check_n(char *str);
void		my_echo(t_commnd *cmd);
char		*ft_strnstr(char *src, char *to_find, size_t n);
char		*ft_strdup(char *s1);
char		*ft_strjoin(char *s1, char *s2);
void		oldpwd(char **envp);
t_env		*ft_lstnew(char *key, char *value);
void		ft_lstadd_front(t_env **lst, t_env *new);
char		*ft_strchr(char *s, int c);
void		my_env(t_commnd *cmd, t_env *lst);
int			ft_len(char *str, char c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			is_spec_carac(char c);
void		ft_lstadd_back(t_env **lst, t_env *new);
t_env		*ft_lstlast(t_env *lst);
int			ft_isalnumm(char str);
int			check_for_signe(char *str, char c);
t_env		*my_export(t_commnd *cmd, t_env *lst, t_utils *utils);
t_env		*copy_env(char **envp, t_env **lst);
t_env		*sort_export(t_env *lst);
int			ft_cheeck(char *str);
t_env		*my_unset(t_commnd *cmd, t_env **env);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		ft_env_remove_if(t_env **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));
size_t		ft_strlen2(char *str);
void		*ft_calloc(size_t count, size_t size);
void		my_cd(t_commnd *cmd, t_env *my_list, t_utils *utils);
int			check_builtins(t_commnd *cmd);
int			my_exit(t_commnd *cmd);
int			count_args(char **str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_lstsize(t_env *lst);
void		exec_builtins(t_commnd *cmd, t_env *lst);
char		*joindre_path(char **save);
void		exec_premiere_cmd(int *fd, char **av, char **envp);
void		exec_deux_cmd(int *fd, char **av, char **envp);
void		ft_free_two_dim(char **ptr);
void		close_and_exit(int *fd);
char		*concat_save(t_env *env, char *commande);
int			ft_lstsize_cmd(t_commnd *lst);
void		execute_cmd(t_commnd *cmd, char **envp);
void		exec(int *fd, t_commnd *cmd, t_env *env, char **o_env);
void		cmd_exc(t_commnd *cmd);
void		open_files(t_commnd *cmd, t_fds *fds,
				t_heredoc **heredocc);
char		**ft_split(char *s, char c);
char		**split_path(char *path);
char		*joindre_my_path(char **path_split);
char		*check_path(t_env *env, t_commnd *cmd);
void		exec_first_cmd(t_commnd *cmd, char **envp,
				t_heredoc **heredocc, t_all *all);
void		exec_2_cmd(t_commnd *cmd, char **envp,
				t_heredoc **heredocc1, t_all *all);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
char		**ft_split(char *s, char c);
int			my_exit(t_commnd *cmd);
int			count_args(char **str);
int			count_heredocs(t_commnd *cmd);
void		open_pipe(t_commnd *cmd, t_pipes *pipes);
int			count_heredocs(t_commnd *cmd);
void		read_heredoc(char *delimit, t_heredoc **heredocc, int i,
				t_commnd *cmd);
int			utils_exit(int i);
void		check_heredoc(t_commnd *cmd, t_heredoc **heredoc);
void		close_all(void);
t_heredoc	*ft_lstnew_heredoc(int data);
void		ft_lstadd_back_heredoc(t_heredoc **heredocc,
				t_heredoc *new);
int			check_find_herdoc(t_commnd **cmd, int i);
void		print_export(t_commnd *cmd, t_env *current);
int			errors_export(t_commnd *cmd, int c, int i);
void		export_plus_case(t_commnd *cmd, t_utils *utils,
				t_env *lst, int i);
char		*ft_sersh_val(t_env *lst, char *str);
t_env		*ft_lstnew(char *key, char *value);
t_heredoc	*ft_lstnew_heredoc(int data);
void		print_errors_cd(int i);
int			open_files_bu(t_commnd *cmd, t_fds *fds,
				t_heredoc **heredocc);
void		cd_helper1(char *test);
void		cd_helper2(t_env *my_list, t_utils *utils);
char		*mise_ajour_pwd_before(t_env *lst);
void		mise_ajour_pwd2_after(t_env **lst, char *new, int c);
void		export_helper(t_commnd *cmd, t_env *lst, int i);
int			ft_search_key(t_env *lst, char *str);
void		unset_helper(t_commnd *cmd, int i);
int			find_not_alphanum(char *str);
void		unset_helper2(t_commnd *cmd, int i, t_env **env,
				t_utils utils);
int			print_errors_files(void);
int			print_errors_files_2(void);
void		open_files_helper(t_commnd *cmd, t_fds *fds, int i);
int			open_files_bu_helper(t_commnd *cmd, t_fds *fds, int i);
void		print_errors_fork(void);
void		print_errors_path(void);
void		print_errors_exceve(void);
void		initi_fds(t_fds *fds);
void		exec_first_cmd_in_pipe(t_commnd *cmd,
				t_heredoc **heredocc, char **envp, t_all *all);
void		exec_cmd_west(t_commnd *cmd, t_heredoc *heredocc,
				t_all *all, char **envp);
void		exec_one_cmd(t_commnd *cmd, char **envp, t_all *all,
				t_heredoc **heredocc);
void		last_cmd(t_commnd *cmd, t_heredoc *heredocc,
				char **envp, t_all *all);
void		helper1(t_commnd *cmd, char **envp, t_all *all,
				t_heredoc **heredocc1);
void		close_pipe2(t_utils *utils);
void		close_pipes(t_utils *utils);
void		print_errors_exec(void);
void		helper2(t_fds *fds, t_utils *utils);
void		print_erros_heredoc(void);
char		*my_pwd2(int i, t_env *lst);
void		signalsss(char **cmd_line);
void		sighandle(int sig);
void		rl_replace_line(const char *text, int clear_undo);
int			ft_execute_bulitins(t_commnd *exec, int mode);
void		ft_free_ddim(char **str);

#endif