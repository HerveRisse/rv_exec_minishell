
#include "parser.h"

/* Recherche un token de redirection (< > >> <<) dans la liste de tokens */
t_token *find_redirections_token(t_token *tokens, t_token *stop)
{
	t_token *last_redir;

	if (!tokens)
		return (NULL);
	last_redir = NULL;
	while (tokens != stop && tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT || tokens->type == APPEND || tokens->type == HEREDOC)
			last_redir = tokens;
		tokens = tokens->next;
	}
	return (last_redir);
}

/* Recherche un token de pipe (|) dans la liste de tokens */
t_token *find_pipe_token(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (NULL);
	while (tokens != stop && tokens)
	{
		if (tokens->type == PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

/* Convertit un type de token en type de noeud AST correspondant */
t_node_type get_type_node(t_token *token)
{
	if (token->type == REDIR_IN)
		return (NODE_REDIR_IN);
	if (token->type == REDIR_OUT)
		return (NODE_REDIR_OUT);
	if (token->type == APPEND)
		return (NODE_APPEND);
	if (token->type == HEREDOC)
		return (NODE_HEREDOC);
	if (token->type == PIPE)
		return (NODE_PIPE);
	return (NODE_INVALID);
}

/* Vérifie si la liste de tokens contient des redirections */
int has_redirections(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (0);
	while (tokens != stop && tokens)
	{
		if (tokens->type == REDIR_IN)
			return (1);
		if (tokens->type == REDIR_OUT)
			return (1);
		if (tokens->type == APPEND)
			return (1);
		if (tokens->type == HEREDOC)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/* Vérifie si la liste de tokens contient un pipe */
int has_pipe(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (0);
	while (tokens != stop && tokens)
	{
		if (tokens->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}