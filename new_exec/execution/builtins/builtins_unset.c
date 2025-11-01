/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:03:24 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:03:30 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	builtin_unset(t_command *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i]))
			unset_env_var(&shell->env, cmd->args[i]);
		else
			return (0);
		i++;
	}
	return (0);
}
