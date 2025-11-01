/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:02:18 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:02:21 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../includes/minishell.h"

static void	print_args(t_command *cmd, t_shell *shell, int start_idx)
{
	int	i;

	(void)shell;
	i = start_idx;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
}

int	builtin_echo(t_command *cmd, t_shell *shell)
{
	int	i;
	int	n_flag;

	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	n_flag = 0;
	i = 1;
	while (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
	{
		printf("arg: %s\n", cmd->args[i]);
		n_flag = 1;
		i++;
	}
	print_args(cmd, shell, i);
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
