
#include "lexer.h"
#include <stdio.h>

char *get_word_expand(char *line, size_t len)
{
	return (ft_strndup(line, len));
}

char *get_word_in_double_quotes(char *line, size_t len)
{
	char *word;

	// Vérifier les paramètres
	if (!line || len < 1)
		return (ft_strdup(""));

	word = ft_strndup(line + 1, len - 1);
	if (!word)
		return (ft_strdup(""));
	return (word);
}
