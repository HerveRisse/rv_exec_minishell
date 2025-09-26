
#include "../execution.h"

/* Libère la mémoire allouée pour une variable d'environnement */
static void	free_env_var(t_env *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

/* Supprime la première variable d'environnement si sa clé correspond */
static int	unset_first_var(t_env **env, char *key)
{
	t_env	*current;

	current = *env;
	if (ft_strcmp(current->key, key) == 0)
	{
		*env = current->next;
		free_env_var(current);
		return (1);
	}
	return (0);
}

/* Supprime une variable d'environnement de la liste chaînée par sa clé */
void	unset_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*env || !key)
		return ;
	if (unset_first_var(env, key))
		return ;
	current = *env;
	prev = NULL;
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_env_var(current);
	}
}
