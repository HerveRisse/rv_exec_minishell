/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:09:06 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:09:22 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../includes/minishell.h"

char	*get_var_value(t_env *env, char *name);

char	*add_char_to_result(char *result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = result;
	result = ft_strjoin(result, buf);
	free(tmp);
	return (result);
}

char	*handle_question_mark(char *result, t_shell *shell)
{
	char	*tmp;
	char	*exit_status_str;

	exit_status_str = ft_itoa(shell->exit_status);
	tmp = result;
	result = ft_strjoin(result, exit_status_str);
	free(tmp);
	free(exit_status_str);
	return (result);
}

char	*expand_var_helper(char *result, char *var_name, t_env *env)
{
	char	*var_value;
	char	*tmp;

	if (!var_name)
		return (result);
	var_value = get_var_value(env, var_name);
	free(var_name);
	tmp = result;
	result = ft_strjoin(result, var_value);
	free(tmp);
	free(var_value);
	return (result);
}

char	*get_var_name_from_str(char *str, int start, int j)
{
	char	*var_name;

	var_name = ft_strndup(str + start, j);
	return (var_name);
}
