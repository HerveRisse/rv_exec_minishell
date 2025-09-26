
#include "parser.h"

t_token	*find_and_token(t_token *tokens, t_token *stop)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current && current != stop)
	{
		if (current->type == AND)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	has_and(t_token *tokens, t_token *stop)
{
	return (find_and_token(tokens, stop) != NULL);
}

t_ast_node	*parse_command_with_and(t_token *tokens, t_token *stop)
{
	t_ast_node	*ast_node;
	t_token		*and_token;

	if (!tokens)
		return (NULL);
	ast_node = malloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	init_ast_node(ast_node);
	and_token = find_and_token(tokens, stop);
	ast_node->type = NODE_AND;
	if (!and_token)
	{
		free_ast(ast_node);
		return (NULL);
	}
	ast_node->left = parse_command(tokens, and_token);
	ast_node->right = parse_command(and_token->next, stop);
	if (!ast_node->left || !ast_node->right)
	{
		free_ast(ast_node);
		return (NULL);
	}
	return (ast_node);
}
