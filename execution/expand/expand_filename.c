
#include "../execution.h"

/* Effectue l'expansion des variables d'environnement dans un nom de fichier */
char	*expand_filename(char *filename, t_env *env)
{
	char	*expanded;

	if (!filename)
		return (NULL);
	if (!ft_strchr(filename, '$'))
		return (ft_strdup(filename));
	expanded = expand_variables(filename, env);
	if (!expanded)
		return (ft_strdup(filename));
	return (expanded);
}
