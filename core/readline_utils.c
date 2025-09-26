
#include "../parser/parser.h"
#include "../execution/execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

static struct termios	g_original_term;
static struct termios	g_custom_term;

/* Wrapper pour readline qui ajoute automatiquement les lignes non vides à l'historique */
char	*simple_readline(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

/* Nettoie les ressources utilisées par readline et sauvegarde l'historique */
void	cleanup_readline(void)
{
	char	*home;
	char	history_path[1024];

	home = getenv("HOME");
	if (home)
	{
		ft_strlcpy(history_path, home, sizeof(history_path));
		ft_strlcat(history_path, "/.minishell_history", sizeof(history_path));
		write_history(history_path);
	}
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_original_term);
}

/* Configure les paramètres du terminal pour le shell */
static void	configure_terminal(void)
{
	tcgetattr(STDIN_FILENO, &g_original_term);
	g_custom_term = g_original_term;
	g_custom_term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &g_custom_term);
}

/* Initialise readline, charge l'historique et configure le terminal */
void	setup_readline(void)
{
	char	*home;
	char	history_path[1024];

	configure_terminal();
	rl_catch_signals = 0;
	using_history();
	home = getenv("HOME");
	if (home)
	{
		ft_strlcpy(history_path, home, sizeof(history_path));
		ft_strlcat(history_path, "/.minishell_history", sizeof(history_path));
		read_history(history_path);
	}
	rl_bind_key('\t', rl_insert);
}
