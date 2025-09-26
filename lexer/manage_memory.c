
#include "lexer.h"

/* Libère la mémoire allouée pour une liste chaînée de segments */
void	free_segments(t_segment *segments)
{
	t_segment	*to_free;

	if (!segments)
		return ;
	while (segments)
	{
		if (segments->word)
			free(segments->word);
		to_free = segments;
		segments = segments->next;
		free(to_free);
	}
}

/* Libère la mémoire allouée pour une liste chaînée de tokens */
void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*to_free;

	if (!head)
		return ;
	current = (*head);
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free->value);
		free(to_free);
	}
	(*head) = NULL;
}
