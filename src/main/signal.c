#include "../../inc/libs.h"

void handle_sigint_main(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_questionvar(shell(), 130);
}

void handle_sigint_heredoc(int sig)
{
	(void)sig;
	global_sig = SIGINT;
	printf("\n");
	close(STDIN_FILENO);
}

void set_sig_main(void)
{
	signal(SIGINT, handle_sigint_main);
	signal(SIGQUIT, SIG_IGN);
}

void set_sig_heredoc(void)
{
	global_sig = 0;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void set_sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void set_sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
