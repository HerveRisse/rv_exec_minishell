
#include "execution.h"

/* Affiche un message d'erreur sur la sortie d'erreur standard */
void	error_msg(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

/* Libère la mémoire allouée pour un tableau de chaînes de caractères */
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
