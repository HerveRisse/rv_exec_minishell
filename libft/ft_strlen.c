/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:30:24 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 14:04:34 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	printf("chaine: %s\n", argv[1]);
	printf("ft_strlen: %zu\n", ft_strlen(argv[1]));
	printf("strlen: %zu\n", strlen(argv[1]));
	return (0);
}*/
