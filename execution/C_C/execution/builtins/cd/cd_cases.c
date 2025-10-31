/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:47:07 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 19:47:16 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"
#include "cd.h"
int	cd_special_dash(t_shell *shell)
{
	t_env *oldpwd_var;

	oldpwd_var = get_env_var(shell->env, "OLDPWD");
	if (!oldpwd_var || !oldpwd_var->value || !oldpwd_var->value[0])
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	ft_putendl_fd(oldpwd_var->value, STDOUT_FILENO);
	if (chdir(oldpwd_var->value) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(oldpwd_var->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int cd_normal_case(t_command *cmd, t_shell *shell)
{
	char *path;
	char *old_pwd;
	char cwd[1024];
	int result;

	result = cd_get_path(cmd, shell, &path);
	if (result)
		return (1);
	old_pwd = getcwd(cwd, sizeof(cwd));
	result = cd_change_directory(path, old_pwd);
	free(path);
	return (result);
}
