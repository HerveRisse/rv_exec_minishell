/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:08:31 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:08:34 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../includes/minishell.h"

char	*get_var_name(char *str, int *i);
char	*get_var_value(t_env *env, char *name);
char	*replace_var(char *str, int start, int end, char *value);
int		is_in_quotes(char *str, int pos, int *in_single, int *in_double);
char	*add_char_to_result(char *result, char c);
char	*handle_question_mark(char *result, t_shell *shell);
char	*expand_var_helper(char *result, char *var_name, t_env *env);
char	*get_var_name_from_str(char *str, int start, int j);
char	*process_variable(char *result, char *str, int *i, t_env *env);
char	*process_char_helper(char *result, char *str, int *i, t_shell *shell);
char	*process_dollar(char *result, char *str, int *i, t_shell *shell);
char	*process_char(char *result, char *str, int *i, t_shell *shell);

char	*expand_variables(char *str, t_env *env)
{
	return (expand_variables_with_shell(str, env, NULL));
}

static char	*handle_quote(char *str, int *i, int *sq, int *dq)
{
	if (str[*i] == '\'' && !(*dq))
	{
		*sq = !(*sq);
		(*i)++;
	}
	else if (str[*i] == '"' && !(*sq))
	{
		*dq = !(*dq);
		(*i)++;
	}
	return (NULL);
}

static char	*process_expand_loop(char *str, char *result, t_shell *shell)
{
	int		i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !dq) || (str[i] == '"' && !sq))
			handle_quote(str, &i, &sq, &dq);
		else if (str[i] == '$' && !sq)
			result = process_char(result, str, &i, shell);
		else
			result = add_char_to_result(result, str[i++]);
	}
	return (result);
}

char	*expand_variables_with_shell(char *str, t_env *env, t_shell *shell)
{
	char	*result;

	(void)env;
	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_expand_loop(str, result, shell));
}
