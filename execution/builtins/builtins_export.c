
#include "../execution.h"

/* Traite une variable à exporter au format KEY=VALUE */
static int	export_var(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
		if (is_valid_identifier(key))
		{
			set_env_var(&shell->env, key, value);
		}
		else
		{
			free(key);
			free(value);
			error_msg("not a valid identifier");
			return (1);
		}
	}
	return (0);
}

/* Implémente la commande builtin export pour définir des variables d'environnement */
int	builtin_export(t_command *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->args[1])
		return (0);
	i = 1;
	while (cmd->args[i])
	{
		if (export_var(shell, cmd->args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
