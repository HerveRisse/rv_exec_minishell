/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:56:22 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:56:25 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>
#include <errno.h>

void	setup_redirections(int in_fd, int out_fd);
int		handle_exec_error(t_command *cmd, char *path, char **env_array);
void	handle_no_path(t_command *cmd, char **env_array);

static void	execute_cmd(t_command *cmd, char **env_array, char *path)
{
	int			exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	execve(path, cmd->args, env_array);
	exit_code = handle_exec_error(cmd, path, env_array);
	free(path);
	free_array(env_array);
	exit(exit_code);
}

static void	child_process(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	char	**env_array;
	char	*path;

	setup_redirections(in_fd, out_fd);
	signal(SIGPIPE, SIG_DFL);
	if (!cmd->args[0] || !cmd->args[0][0])
		exit(0);
	env_array = env_to_array(shell->env);
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
		handle_no_path(cmd, env_array);
	execute_cmd(cmd, env_array, path);
}

void	execute_external(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		child_process(cmd, shell, in_fd, out_fd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}
