
#include "../../execution.h"
#include "cd.h"

/* Met à jour les variables d'environnement PWD et OLDPWD après un changement de répertoire */
void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*pwd_key;
	char	*oldpwd_key;
	char	*pwd_value;
	char	*oldpwd_value;
	t_env	*oldpwd_var;

	pwd_key = ft_strdup("PWD");
	oldpwd_key = ft_strdup("OLDPWD");
	pwd_value = ft_strdup(old_pwd);
	oldpwd_var = get_env_var(shell->env, "PWD");
	if (oldpwd_var && oldpwd_var->value)
		oldpwd_value = ft_strdup(oldpwd_var->value);
	else
		oldpwd_value = ft_strdup(old_pwd);
	set_env_var(&shell->env, pwd_key, pwd_value);
	set_env_var(&shell->env, oldpwd_key, oldpwd_value);
}
