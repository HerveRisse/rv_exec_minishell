
#include "../parser/parser.h"
#include "../execution/execution.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int	g_signal_status;

/* Gère le signal SIGINT (Ctrl+C) pour afficher un nouveau prompt */
void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_status = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* Gère le signal SIGQUIT (Ctrl+\) pour ne rien faire en mode interactif */
void	handle_sigquit(int sig)
{
	(void)sig;
}

/* Configure les gestionnaires de signaux pour Ctrl+C et Ctrl+\ */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}
