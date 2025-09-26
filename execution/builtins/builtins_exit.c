
#include "../execution.h"

/* Implémente la commande builtin exit pour quitter le shell avec un code de sortie optionnel */
int	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->args[1])
	{
		exit_code = ft_atoi(cmd->args[1]);
		shell->exit_status = exit_code;
	}
	shell->running = 0;
	return (shell->exit_status);
}
