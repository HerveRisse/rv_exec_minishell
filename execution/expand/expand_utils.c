
#include "../execution.h"

/* Extrait le nom d'une variable d'environnement à partir d'une position donnée */
char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*name;

	start = *i;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start + 1, *i - start - 1);
	return (name);
}

/* Récupère la valeur d'une variable d'environnement par son nom */
char	*get_var_value(t_env *env, char *name)
{
	t_env	*var;

	var = get_env_var(env, name);
	if (var && var->value)
		return (ft_strdup(var->value));
	return (ft_strdup(""));
}

/* Remplace une variable par sa valeur dans une chaîne de caractères */
char	*replace_var(char *str, int start, int end, char *value)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;

	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + end);
	temp = ft_strjoin(prefix, value);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(str);
	return (result);
}

/* Vérifie si une position dans une chaîne est entre guillemets simples ou doubles */
int	is_in_quotes(char *str, int pos, int *in_single, int *in_double)
{
	int	i;

	*in_single = 0;
	*in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !*in_double)
			*in_single = !*in_single;
		else if (str[i] == '"' && !*in_single)
			*in_double = !*in_double;
		i++;
	}
	return (*in_single || *in_double);
}
