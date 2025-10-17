
#include "../execution.h"
#include "../../includes/minishell.h"

/* Affiche les arguments de la commande echo */
static void	print_args(t_command *cmd, t_shell *shell, int start_idx)
{
	int		i;

	(void)shell;
	i = start_idx;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

/* Implémente la commande builtin echo avec support de l'option -n */
int	builtin_echo(t_command *cmd, t_shell *shell)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	i = 1;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	print_args(cmd, shell, i);
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
