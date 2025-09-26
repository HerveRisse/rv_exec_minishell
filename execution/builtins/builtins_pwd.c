
#include "../execution.h"

/* Implémente la commande builtin pwd pour afficher le répertoire courant */
int	builtin_pwd(t_command *cmd, t_shell *shell)
{
	char	cwd[1024];

	(void)cmd;
	(void)shell;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	else
	{
		error_msg("pwd error");
		return (1);
	}
}
