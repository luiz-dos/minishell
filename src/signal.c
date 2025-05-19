#include "../inc/libs.h"

void	ft_redefine_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_ignore_some_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sigint(int sig)
{
	t_shell	*data;

	data = ft_start_shell();
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		data->return_status = 130;
	}
}

void	hd_ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		global_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	ft_config_signals(int process_type)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigemptyset(&sigint.sa_mask);
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_handler = SIG_IGN;
	if (process_type == 0)
		sigint.sa_handler = ft_handle_sigint; // Shell principal
	else
		sigint.sa_handler = hd_ft_handle_sigint; // Heredoc/filho
	sigint.sa_flags = 0;
	sigquit.sa_flags = 0;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
}
