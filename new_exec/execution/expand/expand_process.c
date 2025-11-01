/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:09:06 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:09:22 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../includes/minishell.h"

char	*add_char_to_result(char *result, char c);
char	*handle_question_mark(char *result, t_shell *shell);
char	*expand_var_helper(char *result, char *var_name, t_env *env);
char	*get_var_name_from_str(char *str, int start, int j);

char	*process_variable(char *result, char *str, int *i, t_env *env)
{
	int		start;
	int		j;

	start = *i + 1;
	j = 0;
	while (str[start + j] && (ft_isalnum(str[start + j])
			|| str[start + j] == '_'))
		j++;
	if (j > 0)
	{
		result = expand_var_helper(result, get_var_name_from_str(str, start, j),
				env);
		*i += j + 1;
	}
	else
	{
		result = add_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*process_char_helper(char *result, char *str, int *i, t_shell *shell)
{
	t_env	*env_to_use;

	if (shell)
		env_to_use = shell->env;
	else
		env_to_use = NULL;
	return (process_variable(result, str, i, env_to_use));
}

char	*process_dollar(char *result, char *str, int *i, t_shell *shell)
{
	if (!str[*i + 1])
	{
		result = add_char_to_result(result, str[*i]);
		(*i)++;
	}
	else if (str[*i + 1] == '?' && shell)
	{
		result = handle_question_mark(result, shell);
		(*i) += 2;
	}
	else if (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		result = process_char_helper(result, str, i, shell);
	else
	{
		result = add_char_to_result(result, str[*i]);
		(*i)++;
	}
	return (result);
}

char	*process_char(char *result, char *str, int *i, t_shell *shell)
{
	if (str[*i] == '$')
		return (process_dollar(result, str, i, shell));
	result = add_char_to_result(result, str[*i]);
	(*i)++;
	return (result);
}
