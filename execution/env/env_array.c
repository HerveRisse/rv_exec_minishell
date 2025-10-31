
#include "../execution.h"

/* Compte le nombre de variables d'environnement dans la liste chaînée */
static int	count_env_vars(t_env *env)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* Crée une chaîne de caractères au format KEY=VALUE pour une variable d'environnement */
static char	*create_env_string(t_env *var)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(var->key, "=");
	result = ft_strjoin(tmp, var->value);
	free(tmp);
	return (result);
}

/* Convertit la liste chaînée des variables d'environnement en tableau de chaînes pour execve */
char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**array;
	int		count;
	int		i;

	count = count_env_vars(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		array[i] = create_env_string(current);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}
