
#include "../parser/parser.h"
#include "../execution/execution.h"

/* Vérifie que la variable PWD existe, la crée si nécessaire */
static void	ensure_pwd_exists(t_env **env)
{
	t_env	*pwd_var;
	char	*key;
	char	*value;
	char	cwd[1024];

	pwd_var = get_env_var(*env, "PWD");
	if (!pwd_var)
	{
		key = ft_strdup("PWD");
		if (getcwd(cwd, sizeof(cwd)))
			value = ft_strdup(cwd);
		else
			value = ft_strdup("");
		add_env_var(env, key, value);
	}
}

/* Vérifie que la variable OLDPWD existe, la crée si nécessaire */
static void	ensure_oldpwd_exists(t_env **env)
{
	t_env	*oldpwd_var;
	t_env	*pwd_var;
	char	*key;
	char	*value;
	char	cwd[1024];

	oldpwd_var = get_env_var(*env, "OLDPWD");
	pwd_var = get_env_var(*env, "PWD");
	if (!oldpwd_var)
	{
		key = ft_strdup("OLDPWD");
		if (pwd_var && pwd_var->value)
			value = ft_strdup(pwd_var->value);
		else if (getcwd(cwd, sizeof(cwd)))
			value = ft_strdup(cwd);
		else
			value = ft_strdup("");
		add_env_var(env, key, value);
	}
}

/* Initialise l'environnement du shell à partir des variables d'environnement du système */
t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	char	*key;
	char	*value;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		parse_env_var(envp[i], &key, &value);
		if (key)
			add_env_var(&env, key, value);
		i++;
	}
	ensure_pwd_exists(&env);
	ensure_oldpwd_exists(&env);
	return (env);
}
