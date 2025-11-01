/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:52:46 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:52:49 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <string.h>

int	process_heredoc_node(t_ast_node *node, t_shell *shell)
{
	int	tmp_in;
	int	ret;

	tmp_in = STDIN_FILENO;
	ret = setup_redirection(node, &tmp_in, NULL, shell);
	if (ret == 0 && tmp_in != STDIN_FILENO)
	{
		dup2(tmp_in, STDIN_FILENO);
		close(tmp_in);
	}
	else if (ret != 0)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

int	process_redir_in(t_ast_node *node, t_shell *shell)
{
	int	fd;

	fd = open(node->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	process_redir_out(t_ast_node *node, t_shell *shell)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (node->type == NODE_APPEND)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(node->filename, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->filename, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		shell->exit_status = 1;
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
