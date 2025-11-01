/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 19:58:33 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 19:58:43 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"
#include "cd.h"

void	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*pwd_key;
	char	*oldpwd_key;
	char	*pwd_value;
	char	*oldpwd_value;
	t_env	*oldpwd_var;

	pwd_key = ft_strdup("PWD");
	oldpwd_key = ft_strdup("OLDPWD");
	pwd_value = ft_strdup(old_pwd);
	oldpwd_var = get_env_var(shell->env, "PWD");
	if (oldpwd_var && oldpwd_var->value)
		oldpwd_value = ft_strdup(oldpwd_var->value);
	else
		oldpwd_value = ft_strdup(old_pwd);
	set_env_var(&shell->env, pwd_key, pwd_value);
	set_env_var(&shell->env, oldpwd_key, oldpwd_value);
}
