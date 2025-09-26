
#include "lexer.h"
#include <stdio.h>

/* Détermine l'état du lexer en fonction du caractère courant */
int	get_state(int c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	if (c == '$')
		return (3);
	return (0);
}

/* Concatène deux chaînes et libère la mémoire des deux chaînes d'origine */
char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*temp;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

/* Extrait un mot complet de la ligne, en gérant les guillemets et les opérateurs */
char	*get_full_word(char **line)
{
	char	*full_word;
	char	*part;

	full_word = ft_strdup("");
	while (**line && !is_space(**line) && !is_operator(*line))
	{
		if (**line == '\'')
			part = extract_word_simple_quotes(line);
		else if (**line == '\"')
			part = extract_word_double_quotes(line);
		else if (**line == '$')
			part = extract_variable(line);
		else
			part = extract_word_without_quotes(line);
		if (!part)
		{
			free(full_word);
			return (NULL);
		}
		full_word = ft_strjoin_and_free(full_word, part);
		if (!full_word)
			return (NULL);
	}
	return (full_word);
}

/* Extrait le prochain mot ou opérateur de la ligne, en ignorant les espaces */
char	*get_word(char **line)
{
	char	*full_word;

	remove_space(line);
	if (is_operator(*line))
		return (extract_operator(line));
	full_word = get_full_word(line);
	remove_space(line);
	return (full_word);
}
