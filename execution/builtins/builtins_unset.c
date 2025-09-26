
#include "../execution.h"

/* Implémente la commande builtin unset pour supprimer des variables d'environnement */
int	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
			unset_env_var(&shell->env, cmd->args[i]);
		else
		{
			error_msg("not a valid identifier");
			return (1);
		}
		i++;
	}
	return (0);
}
