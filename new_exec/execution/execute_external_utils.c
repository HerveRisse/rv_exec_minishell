/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_utils.c                           :+:      :+:    :+:   */
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

void	setup_redirections(int in_fd, int out_fd)
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

int	handle_enoexec(t_command *cmd, char *path, char **env_array)
{
	cmd->args[0] = path;
	execve("/bin/sh", cmd->args, env_array);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int	handle_eacces(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (error_msg("Is a directory"), 126);
	ft_putstr_fd("minishell: ", 2);
	perror(path);
	return (126);
}

int	handle_exec_error(t_command *cmd, char *path, char **env_array)
{
	if (errno == ENOEXEC)
		return (handle_enoexec(cmd, path, env_array));
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		return (127);
	}
	if (errno == EACCES && ft_strchr(path, '/'))
		return (handle_eacces(path));
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

void	handle_no_path(t_command *cmd, char **env_array)
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
