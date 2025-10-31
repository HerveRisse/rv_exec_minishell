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

static void	setup_redirections(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static void	execute_cmd(t_command *cmd, char **env_array, char *path)
{
	struct stat	path_stat;
	int			exit_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	execve(path, cmd->args, env_array);
	exit_code = 127;
	if (errno == ENOEXEC)
	{
		cmd->args[0] = path;
		execve("/bin/sh", cmd->args, env_array);
		ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(cmd->args[0], 2);
    	ft_putendl_fd(": command not found", 2);
		exit_code = 127;
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		exit_code = 127;
	}
	else if (errno == EACCES && ft_strchr(path, '/'))
	{
		if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			error_msg("Is a directory");
			exit_code = 126;
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			perror(path);
			exit_code = 126;
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
    	ft_putstr_fd(cmd->args[0], 2);
    	ft_putendl_fd(": command not found", 2);
		exit_code = 127;
	}
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
	{
		exit(0);
	}
	env_array = env_to_array(shell->env);
	path = find_command_path(cmd->args[0], shell->env);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->args[0]);
			free_array(env_array);
			exit(127);
		}
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_array(env_array);
		exit(127);
	}

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
