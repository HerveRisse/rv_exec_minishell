
#include "parser.h"

/* Recherche un token de redirection (< > >> <<) dans la liste de tokens */
t_token	*find_redirections_token(t_token *tokens, t_token *stop)
{
	if (!tokens)
		return (NULL);
	while (tokens != stop && tokens)
	{
		if (tokens->type == REDIR_IN)
			return (tokens);
		if (tokens->type == REDIR_OUT)
			return (tokens);
		if (tokens->type == APPEND)
			return (tokens);
		if (tokens->type == HEREDOC)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

/* Recherche un token de pipe (|) dans la liste de tokens */
t_token	*find_pipe_token(t_token *tokens, t_token *stop)
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
t_node_type	get_type_node(t_token *token)
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
int	has_redirections(t_token *tokens, t_token *stop)
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
int	has_pipe(t_token *tokens, t_token *stop)
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

/*void	print_ast_node(t_ast_node *node)
{
	char	**words;
	size_t	i;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		printf("type node: NODE_COMMAND\n");
	else if (node->type == NODE_REDIR_IN)
		printf("type node: NODE_REDIR_IN\n");
	else if (node->type == NODE_REDIR_OUT)
		printf("type node: NODE_REDIR_OUT\n");
	else if (node->type == NODE_APPEND)
		printf("type node: NODE_APPEND\n");
	else if (node->type == NODE_HEREDOC)
		printf("type node: NODE_HEREDOC\n");
	else if (node->type == NODE_PIPE)
		printf("type node: NODE_PIPE\n");
	else if (node->type == NODE_INVALID)
		printf("type node: NODE_INVALID\n");
	if (node->cmd)
	{
		printf("args: ");
		words = node->cmd->args;
		i = 0;
		while (words[i])
		{
			printf("%s ", words[i]);
			i++;
		}
		printf("\n");
	}
	if (node->filename)
		printf("filename: %s\n", node->filename);
	if (node->left)
	{
		printf("LEFT: ");
		print_ast_node(node->left);
	}
	if (node->right)
	{
		printf("RIGHT ");
		print_ast_node(node->right);
	}
}*/
