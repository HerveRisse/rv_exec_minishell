
#include "../execution.h"

/* Vérifie si une chaîne est un identifiant valide pour une variable (commence par une lettre, suivi de lettres, chiffres ou _) */
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || !ft_isalpha(*str))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
