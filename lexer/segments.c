
#include "lexer.h"
#include <stdio.h>

void update_segments(t_segment **head, t_segment **tail, t_segment *new)
{
	if (!*head)
	{
		(*head) = new;
		(*tail) = new;
	}
	else
	{
		(*tail)->next = new;
		(*tail) = new;
	}
}

t_segment *create_segments(char *word)
{
	t_segment *head;
	t_segment *tail;
	t_segment *new;
	char *current;
	size_t len;

	if (!word || !*word)
		return (NULL);
	current = word;
	head = NULL;
	tail = NULL;
	while (*current)
	{
		len = get_len_segment_word(current);
		new = create_new_segment(head, current, len);
		if (!new)
			return (NULL);
		update_segments(&head, &tail, new);
		// Avancer le pointeur en fonction du type et de la longueur
		if (new->type == 0 || len == 0)
			current += (len > 0) ? len : 1;
		else if (*(current + len + 1)) // Vérifier qu'on ne dépasse pas la fin de la chaîne
			current += len + 1;
		else
			current += len;
	}
	return (head);
}