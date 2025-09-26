
#include "parser.h"

void	free_command(t_command *cmd)
{
	char	**words;
	size_t	i;

	if (!cmd)
		return ;
	words = cmd->args;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(cmd->args);
	free(cmd);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->cmd)
		free_command(node->cmd);
	if (node->filename)
		free(node->filename);
	free(node);
}
