/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:52:46 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:52:49 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <string.h>

int	process_heredoc_node(t_ast_node *node, t_shell *shell);
int	process_redir_in(t_ast_node *node, t_shell *shell);
int	process_redir_out(t_ast_node *node, t_shell *shell);

int	is_redirection_node(t_ast_node *node)
{
	return (node->type == NODE_REDIR_IN || node->type == NODE_REDIR_OUT
		|| node->type == NODE_APPEND || node->type == NODE_HEREDOC);
}

void	setup_std_descriptors(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
}

void	setup_tmp_descriptors(int tmp_in, int tmp_out)
{
	if (tmp_in != STDIN_FILENO)
	{
		dup2(tmp_in, STDIN_FILENO);
		close(tmp_in);
	}
	if (tmp_out != STDOUT_FILENO)
	{
		dup2(tmp_out, STDOUT_FILENO);
		close(tmp_out);
	}
}

int	process_redirection_node(t_ast_node *node, t_shell *shell)
{
	if (node->type == NODE_REDIR_IN)
		return (process_redir_in(node, shell));
	else if (node->type == NODE_REDIR_OUT || node->type == NODE_APPEND)
		return (process_redir_out(node, shell));
	else if (node->type == NODE_HEREDOC)
		return (process_heredoc_node(node, shell));
	return (0);
}
