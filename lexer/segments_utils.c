
#include "lexer.h"
#include <stdio.h>

char	*convert_segments_to_str(t_segment *segments)
{
	char	*word;
	size_t	len;
	size_t	i;
	size_t	j;

	len = get_len_from_segments(segments);
	if (!segments || !len)
		return (NULL);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len && segments)
	{
		j = 0;
		while (segments->word[j])
			word[i++] = segments->word[j++];
		segments = segments->next;
	}
	word[i] = 0;
	return (word);
}

t_segment	*create_new_segment(t_segment *head, char *current, size_t len)
{
	t_segment	*new;

	if (!len)
	{
		free_segments(head);
		return (NULL);
	}
	new = malloc(sizeof(t_segment));
	if (!new)
	{
		free_segments(head);
		return (NULL);
	}
	set_word_and_type_segment(new, current, len);
	if (!new->word)
	{
		free(new);
		free_segments(head);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	set_word_and_type_segment(t_segment *segment, char *word, size_t len)
{
	if (!segment || !word)
		return ;
	
	// Conserver le type pour compatibilité
	if (word[0] == '$')
		segment->type = 1;
	else
		segment->type = 0;
	
	// Toujours conserver le mot tel quel, sans expansion
	segment->word = ft_strndup(word, len);
}

size_t	get_len_segment_word(char *word)
{
	size_t	len;

	if (!word)
		return (0);
	len = 0;
	if (word[0] != '$')
	{
		while (word[len] != '$' && word[len])
			len++;
	}
	else
	{
		len = 1;
		if (!word[len])
			return (1); // Retourne 1 pour traiter $ seul
		if (word[len] == '?')
			return (2); // Retourne 2 pour $?
		if (!ft_isalpha(word[len]) && word[len] != '_')
			return (1);
		while ((ft_isalnum(word[len]) || word[len] == '_')
			&& word[len])
			len++;
		return (len - 1);
	}
	return (len);
}

size_t	get_len_from_segments(t_segment *segments)
{
	size_t	len_words;

	if (!segments)
		return (0);
	if (!segments->word[0])
		return (1);
	len_words = 0;
	while (segments)
	{
		if (!segments->word)
			return (0);
		len_words += ft_strlen(segments->word);
		segments = segments->next;
	}
	return (len_words);
}
