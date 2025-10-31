
#include "../execution.h"

/* Extrait la clé d'une variable d'environnement au format KEY=VALUE */
static char	*extract_key(char *env_str, int i)
{
	char	*key;

	key = malloc(i + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_str, i + 1);
	return (key);
}

/* Extrait la valeur d'une variable d'environnement au format KEY=VALUE */
static char	*extract_value(char *env_str, int i)
{
	char	*value;

	if (env_str[i] == '=')
		value = ft_strdup(env_str + i + 1);
	else
		value = ft_strdup("");
	return (value);
}

/* Analyse une chaîne de variable d'environnement et sépare la clé et la valeur */
void	parse_env_var(char *env_str, char **key, char **value)
{
	int	i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	*key = extract_key(env_str, i);
	*value = extract_value(env_str, i);
}
