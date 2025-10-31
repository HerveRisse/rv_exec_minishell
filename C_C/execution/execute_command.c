/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:56:10 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:56:13 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_command(t_ast_node *ast, t_shell *shell, int in_fd, int out_fd)
{
	if (!ast || !ast->cmd || !ast->cmd->args || !ast->cmd->args[0])
		return ;
	if (is_builtin(ast->cmd->args[0]))
		execute_builtin(ast->cmd, shell, in_fd, out_fd);
	else
		execute_external(ast->cmd, shell, in_fd, out_fd);
}
