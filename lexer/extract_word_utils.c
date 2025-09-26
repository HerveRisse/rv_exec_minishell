
#include "lexer.h"
#include <stdio.h>

// Cette fonction ne peut pas utiliser get_env_var car elle n'a pas accès à l'environnement du shell
// Elle est appelée lors de la tokenisation, avant l'expansion des variables
// Nous allons donc simplement conserver la variable telle quelle pour qu'elle soit traitée plus tard
char	*get_word_expand(char *line, size_t len)
{
	// Au lieu d'essayer d'obtenir la valeur de la variable maintenant,
	// nous allons simplement retourner la variable telle quelle (avec le $)
	// pour qu'elle soit traitée plus tard par expand_variables_with_shell
	return (ft_strndup(line, len));
}

// Fonction auxiliaire pour vérifier si une chaîne contient un $ qui n'est pas à la fin
static int	contains_dollar_var(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && 
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			return (1);
		i++;
	}
	return (0);
}

// Fonction auxiliaire pour remplacer $? par une chaîne vide (sera remplacé plus tard)
static char *replace_exit_status(char *str)
{
	char *result;
	char *ptr;
	int len;
	int i;
	int j;

	if (!str)
		return (NULL);

	// Compter le nombre de $? dans la chaîne
	ptr = str;
	len = ft_strlen(str);
	while ((ptr = ft_strnstr(ptr, "$?", ft_strlen(ptr))))
	{
		len -= 1; // On remplace $? (2 chars) par un placeholder (1 char)
		ptr += 2;
	}

	// Allouer la nouvelle chaîne
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);

	// Copier la chaîne en remplaçant $? par un placeholder
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			result[j++] = '\1'; // Placeholder pour $?
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';

	return (result);
}

char	*get_word_in_double_quotes(char *line, size_t len)
{
	char		*word;
	char		*tmp;
	char		*processed;
	t_segment	*segments;

	// Vérifier les paramètres
	if (!line || len < 1)
		return (ft_strdup(""));

	tmp = ft_strndup(line + 1, len - 1);
	if (!tmp)
		return (ft_strdup(""));

	// Vérifier si la chaîne contient $?
	if (ft_strnstr(tmp, "$?", ft_strlen(tmp)))
	{
		// Cas spécial pour $? seul
		if (ft_strlen(tmp) == 2 && tmp[0] == '$' && tmp[1] == '?')
		{
			word = ft_strdup(tmp);
			free(tmp);
			return (word);
		}
		
		// Remplacer $? par un placeholder
		processed = replace_exit_status(tmp);
		free(tmp);
		if (!processed)
			return (ft_strdup(""));
		tmp = processed;
	}

	// Si la chaîne ne contient pas de variable à développer, on la retourne telle quelle
	if (!contains_dollar_var(tmp))
	{
		return (tmp);
	}

	// Traitement normal avec segments
	segments = create_segments(tmp);
	if (!segments)
	{
		free(tmp);
		return (ft_strdup(""));
	}

	word = convert_segments_to_str(segments);
	free(tmp);
	free_segments(segments);
	return (word ? word : ft_strdup(""));
}
