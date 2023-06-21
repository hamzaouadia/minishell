#include "minishell.h"

void    sighandle(int sig)
{
    (void)sig;
    g_global.exit_code = 1;
    write(2, "\n", 1);
    // rl_replace_line("", 0);
    // rl_on_new_line();
    // rl_redisplay();
}

void    signalsss(char **cmd_line)
{
    struct termios    term;
    struct termios    oldterm;

    signal(SIGINT, sighandle);
    signal(SIGQUIT, SIG_IGN);
    tcgetattr(0, &term);
    tcgetattr(0, &oldterm);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(0, TCSANOW, &term);
    *cmd_line = readline("minishell> ");
    tcsetattr(0, TCSANOW, &oldterm);
}

