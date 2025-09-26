
#include "../execution.h"
#include "cd/cd.h"

/* Implémente la commande builtin cd pour changer de répertoire */
int	builtin_cd(t_command *cmd, t_shell *shell)
{
	char	*old_pwd;
	int		result;

	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		result = cd_special_dash(shell);
	else
		result = cd_normal_case(cmd, shell);
	if (result)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving directory\n", 2);
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	free(old_pwd);
	return (0);
}
