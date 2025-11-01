/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:02:04 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:02:07 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "cd/cd.h"

int	builtin_cd(t_command *cmd, t_shell *shell)
{
	char	*old_pwd;
	int		result;

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-") == 0)
		result = cd_special_dash(shell);
	else
		result = cd_normal_case(cmd, shell);
	if (result)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		ft_putstr_fd("minishell: cd: error retrieving directory\n", 2);
		return (1);
	}
	update_pwd_vars(shell, old_pwd);
	free(old_pwd);
	return (0);
}
