/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:08:47 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:08:51 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*expand_filename(char *filename, t_env *env)
{
	char	*expanded;

	if (!filename)
		return (NULL);
	if (!ft_strchr(filename, '$'))
		return (ft_strdup(filename));
	expanded = expand_variables(filename, env);
	if (!expanded)
		return (ft_strdup(filename));
	return (expanded);
}
