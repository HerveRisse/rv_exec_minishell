
#include "includes/minishell.h"
#include <stdio.h>

int g_signal_status = 0;

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_shell shell;

	(void)argc;
	(void)argv;
	setup_signals();
	setup_readline();
	shell.env = init_env(envp);
	shell.exit_status = 0;
	shell.running = 1;
	while (shell.running)
	{
		g_signal_status = 0;
		line = simple_readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			process_line(line, &shell);
		free(line);
	}
	free_env(shell.env);
	cleanup_readline();
	return (shell.exit_status);
}
