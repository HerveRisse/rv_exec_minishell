
#include "../execution.h"

/* Vérifie si une chaîne est un nombre valide (avec signe optionnel) */
static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Implémente la commande builtin exit pour quitter le shell avec un code de sortie optionnel */
int	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->args[1])
	{
		/* Vérifier que l'argument est un nombre valide */
		if (!is_valid_number(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			shell->exit_status = 2;
			shell->running = 0;
			return (2);
		}
		/* Vérifier qu'il n'y a pas trop d'arguments */
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi(cmd->args[1]);
		shell->exit_status = exit_code;
	}
	shell->running = 0;
	return (shell->exit_status);
}
