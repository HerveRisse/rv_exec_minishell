
#include "lexer.h"

/* Vérifie si un caractère est un espace ou une tabulation */
int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

/* Vérifie si un caractère est un guillemet simple ou double */
int	is_quotes(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/* Vérifie si la ligne commence par un opérateur (>, >>, <, <<, |, &&) */
int	is_operator(char *line)
{
	if (!ft_strncmp(line, ">>", 2))
		return (1);
	else if (!ft_strncmp(line, "<<", 2))
		return (1);
	else if (!ft_strncmp(line, "&&", 2))
		return (1);
	if (*line == '>' || *line == '<')
		return (1);
	if (*line == '|')
		return (1);
	return (0);
}

/* Avance le pointeur de ligne pour sauter les espaces au début */
void	remove_space(char **line)
{
	char	*l;

	if (!line || !*line)
		return ;
	l = (*line);
	while (is_space(*l) && *l)
		l++;
	(*line) = l;
}

/* Duplique une chaîne de caractères avec une longueur maximale spécifiée */
char	*ft_strndup(char *str, size_t len)
{
	char	*s;
	size_t	i;

	if (!str)
		return (NULL);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (i < len && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
