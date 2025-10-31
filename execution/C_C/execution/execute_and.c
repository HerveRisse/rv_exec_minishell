/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:55:58 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:56:02 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	execute_and(t_ast_node *ast, t_shell *shell)
{
	execute_ast(ast->left, shell);
	if (shell->exit_status == 0)
		execute_ast(ast->right, shell);
}
