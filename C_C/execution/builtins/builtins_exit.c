/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:02:45 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:02:47 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_orverflow(char *str)
{
	if (!ft_strncmp(str, "9223372036854775807", 18))
	{
		if (str[18] - '0' > 7)
			return (1);
	}
	if (!ft_strncmp(str, "-9223372036854775808", 19))
	{
		if (str[19] - '0' > 8)
			return (1);
	}
	return (0);
}


static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (is_orverflow(str))
		return (0);
	return (1);
}

int	builtin_exit(t_command *cmd, t_shell *shell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->args[1])
	{
		if (!is_valid_number(cmd->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			shell->exit_status = 2;
			shell->running = 0;
			return (2);
		}
		if (cmd->args[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (1);
		}
		exit_code = ft_atoi(cmd->args[1]);
		shell->exit_status = exit_code;
	}
	shell->running = 0;
	return (shell->exit_status);
}
