/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:52:12 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:52:17 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "redirection.h"

static t_ast_node	*find_command_node(t_ast_node *ast, t_shell *shell)
{
	t_ast_node	*cmd_node;

	if (ast->type == NODE_COMMAND)
		return (ast);
	
	if (is_redirection_node(ast))
	{
		cmd_node = find_command_node(ast->left, shell);
		
		if (cmd_node && process_redirection_node(ast, shell) != 0)
			return (NULL);
		
		return (cmd_node);
	}
	
	if (ast->left)
		return (find_command_node(ast->left, shell));
	
	return (NULL);
}

void	execute_redirection(t_ast_node *ast, t_shell *shell)
{
	int			stdin_copy;
	int			stdout_copy;
	t_ast_node	*cmd_node;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	
	cmd_node = find_command_node(ast, shell);
	
	if (cmd_node)
		execute_ast(cmd_node, shell);
	
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}
