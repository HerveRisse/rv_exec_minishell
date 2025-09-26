
#include "execution.h"

/* Récupère la valeur de la variable d'environnement PATH */
char	*get_path_value(t_env *env)
{
	t_env	*path_var;

	path_var = get_env_var(env, "PATH");
	if (path_var)
		return (path_var->value);
	return (NULL);
}

/* Essaie de trouver le chemin complet d'une commande en testant tous les chemins du PATH */
static char	*try_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(paths);
	return (ft_strdup(cmd));
}

/* Recherche le chemin complet d'une commande en utilisant la variable PATH */
char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strdup(cmd));
	path_value = get_path_value(env);
	if (!path_value)
		return (ft_strdup(cmd));
	paths = ft_split(path_value, ':');
	if (!paths)
		return (ft_strdup(cmd));
	return (try_paths(cmd, paths));
}
