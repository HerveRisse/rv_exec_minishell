
#include "../execution.h"

/* Ajoute une nouvelle variable d'environnement à la liste chaînée */
void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_var;
	t_env	*current;

	if (!key)
		return ;
	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return ;
	new_var->key = key;
	new_var->value = value;
	new_var->next = NULL;
	if (!*env)
		*env = new_var;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_var;
	}
}

/* Recherche une variable d'environnement par sa clé */
t_env	*get_env_var(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*var;

	var = get_env_var(*env, key);
	if (var)
	{
		free(var->value);
		var->value = value;
		free(key);
	}
	else
		add_env_var(env, key, value);
}
