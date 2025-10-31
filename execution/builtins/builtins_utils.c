
#include "../execution.h"

/* Vérifie si une chaîne est un identifiant valide pour une variable (commence par une lettre, suivi de lettres, chiffres ou _) */
/*int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}*/

int is_valid_identifier(char *str)
{
    int i;
    char *equal;
    int name_len;
    
    if (!str || !*str)
        return (0);
    
    // Trouver le '=' s'il existe
    equal = ft_strchr(str, '=');
    
    // Longueur du nom à valider (avant le '=')
    if (equal)
        name_len = equal - str;
    else
        name_len = ft_strlen(str);
    
    // Nom vide (cas "=value")
    if (name_len == 0)
        return (0);
    
    // Premier caractère : lettre ou underscore
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    
    // Caractères suivants : lettre, chiffre ou underscore
    i = 1;
    while (i < name_len)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    
    return (1);
}
