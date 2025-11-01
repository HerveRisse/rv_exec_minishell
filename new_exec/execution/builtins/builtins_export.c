/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:02:56 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:02:59 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

#include "../execution.h"

static void	print_escaped_value(const char *value)
{
	while (*value)
	{
		if (*value == '\\' || *value == '\"')
			write(1, "\\", 1);
		write(1, value, 1);
		value++;
	}
}

void	print_exported_variable(t_shell *shell)
{
	t_env	*tmp;

	if (!shell)
		return ;
	tmp = shell->env;
	while (tmp)
	{
		write(1, "declare -x ", 11);
		write(1, tmp->key, ft_strlen(tmp->key));
		if (tmp->value)
		{
			write(1, "=\"", 2);
			print_escaped_value(tmp->value);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

static int	export_with_value(t_shell *shell, char *arg, char *equal_sign)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (is_valid_identifier(key))
	{
		set_env_var(&shell->env, key, value);
		return (0);
	}
	free(key);
	free(value);
	error_msg("not a valid identifier");
	return (1);
}

static int	export_var(t_shell *shell, char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		return (export_with_value(shell, arg, equal_sign));
	if (!is_valid_identifier(arg))
	{
		error_msg("not a valid identifier");
		return (1);
	}
	return (0);
}

int	builtin_export(t_command *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !shell)
		return (0);
	i = 1;
	if (!cmd->args[1])
	{
		print_exported_variable(shell);
		return (0);
	}
	while (cmd->args[i])
	{
		if (export_var(shell, cmd->args[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
