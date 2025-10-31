/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:06:34 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:06:39 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	free_env_var(t_env *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

static int	unset_first_var(t_env **env, char *key)
{
	t_env	*current;

	current = *env;
	if (ft_strcmp(current->key, key) == 0)
	{
		*env = current->next;
		free_env_var(current);
		return (1);
	}
	return (0);
}

void	unset_env_var(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*env || !key)
		return ;
	if (unset_first_var(env, key))
		return ;
	current = *env;
	prev = NULL;
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free_env_var(current);
	}
}
