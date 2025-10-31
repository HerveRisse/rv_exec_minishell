/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrisse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:03:41 by hrisse            #+#    #+#             */
/*   Updated: 2025/10/31 20:03:44 by hrisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int is_valid_identifier(char *str)
{
    int i;
    char *equal;
    int name_len;
    
    if (!str || !*str)
        return (0);
    
    equal = ft_strchr(str, '=');
    
    if (equal)
        name_len = equal - str;
    else
        name_len = ft_strlen(str);
    
    if (name_len == 0)
        return (0);
    
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return (0);
    
    i = 1;
    while (i < name_len)
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    
    return (1);
}
