/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:00:52 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:00:56 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "cat_heredoc") == 0);
}

static void	execute_echo_to_exit(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		shell->exit_status = builtin_echo(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		shell->exit_status = builtin_cd(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		shell->exit_status = builtin_pwd(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		shell->exit_status = builtin_export(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		shell->exit_status = builtin_unset(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		shell->exit_status = builtin_env(cmd, shell);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		shell->exit_status = builtin_exit(cmd, shell);
}

void	execute_builtin(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	execute_echo_to_exit(cmd, shell);
	if (ft_strcmp(cmd->args[0], "cat_heredoc") == 0)
		shell->exit_status = builtin_cat_heredoc(cmd, shell);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
