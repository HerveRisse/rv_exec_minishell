
#include "../execution.h"

/* Implémente la commande builtin env pour afficher les variables d'environnement */
int	builtin_env(t_command *cmd, t_shell *shell)
{
	t_env	*current;

	(void)cmd;
	current = shell->env;
	while (current)
	{
		if (current->value && *current->value)
		{
			ft_putstr_fd(current->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		current = current->next;
	}
	return (0);
}
