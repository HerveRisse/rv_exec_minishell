/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:09:06 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:09:22 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*name;

	start = *i;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	name = ft_substr(str, start + 1, *i - start - 1);
	return (name);
}

char	*get_var_value(t_env *env, char *name)
{
	t_env	*var;

	var = get_env_var(env, name);
	if (var && var->value)
		return (ft_strdup(var->value));
	return (ft_strdup(""));
}

char	*replace_var(char *str, int start, int end, char *value)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;

	prefix = ft_substr(str, 0, start);
	suffix = ft_strdup(str + end);
	temp = ft_strjoin(prefix, value);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(str);
	return (result);
}

int	is_in_quotes(char *str, int pos, int *in_single, int *in_double)
{
	int	i;

	*in_single = 0;
	*in_double = 0;
	i = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !*in_double)
			*in_single = !*in_single;
		else if (str[i] == '"' && !*in_single)
			*in_double = !*in_double;
		i++;
	}
	return (*in_single || *in_double);
}
