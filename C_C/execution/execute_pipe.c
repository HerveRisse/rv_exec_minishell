/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:56:33 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:56:36 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	execute_left_command(int *pipe_fd, t_ast_node *left,
		t_shell *shell)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	signal(SIGPIPE, SIG_DFL);
	execute_ast(left, shell);
	exit(shell->exit_status);
}

static void	execute_right_command(int *pipe_fd, t_ast_node *right,
		t_shell *shell)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	signal(SIGPIPE, SIG_DFL);
	execute_ast(right, shell);
	exit(shell->exit_status);
}

static void	setup_pipe(int *pipe_fd, t_ast_node *ast, t_shell *shell,
		int *saved_stdin, pid_t *pid1, pid_t *pid2)
{
	*saved_stdin = dup(STDIN_FILENO);
	*pid1 = fork();
	if (*pid1 == 0)
		execute_left_command(pipe_fd, ast->left, shell);
	*pid2 = fork();
	if (*pid2 == 0)
		execute_right_command(pipe_fd, ast->right, shell);
}

void	execute_pipe(t_ast_node *ast, t_shell *shell)
{
	int		pipe_fd[2];
	int		status;
	int		saved_stdin;
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	setup_pipe(pipe_fd, ast, shell, &saved_stdin, &pid1, &pid2);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}
