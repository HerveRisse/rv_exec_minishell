/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:56:54 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:56:56 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_ast(t_ast_node *ast, t_shell *shell)
{
	if (!ast)
		return ;
	if (ast->type == NODE_COMMAND)
		execute_command(ast, shell, STDIN_FILENO, STDOUT_FILENO);
	else if (ast->type == NODE_PIPE)
		execute_pipe(ast, shell);
	else if (ast->type == NODE_REDIR_IN || ast->type == NODE_REDIR_OUT
		|| ast->type == NODE_APPEND || ast->type == NODE_HEREDOC)
		execute_redirection(ast, shell);
}
