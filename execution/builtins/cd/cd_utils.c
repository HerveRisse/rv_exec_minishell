
#include "../../execution.h"
#include "cd.h"

/* Gère le cas où cd est appelé sans argument (utilise HOME) */
int	cd_handle_home(t_shell *shell, char **path)
{
	t_env	*home_var;

	home_var = get_env_var(shell->env, "HOME");
	if (!home_var || !home_var->value)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	*path = ft_strdup(home_var->value);
	return (0);
}

/* Gère le cas où cd est appelé avec l'argument '-' (utilise OLDPWD) */
int	cd_handle_oldpwd(t_shell *shell, char **path)
{
	t_env	*oldpwd_var;

	oldpwd_var = get_env_var(shell->env, "OLDPWD");
	if (!oldpwd_var || !oldpwd_var->value || !oldpwd_var->value[0])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	*path = ft_strdup(oldpwd_var->value);
	ft_putendl_fd(*path, STDOUT_FILENO);
	return (0);
}

/* Détermine le chemin à utiliser pour cd en fonction des arguments */
int	cd_get_path(t_command *cmd, t_shell *shell, char **path)
{
	if (!cmd->args[1])
		return (cd_handle_home(shell, path));
	else if (ft_strcmp(cmd->args[1], "-") == 0)
		return (cd_handle_oldpwd(shell, path));
	else
		*path = ft_strdup(cmd->args[1]);
	return (0);
}

/* Change le répertoire courant et gère les erreurs */
int	cd_change_directory(char *path, char *old_pwd)
{
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving current directory\n", 2);
		return (1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}
