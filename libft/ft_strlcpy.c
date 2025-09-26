/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saif-eddine <saif-eddine@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:08:19 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/05/20 22:10:35 by saif-eddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <bsd/string.h>
// #include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	len_src;

	if (!dst || !src)
		return (0);
	len_src = 0;
	i = 0;
	while (src[len_src])
		len_src++;
	if (siz == 0)
		return (len_src);
	while (src[i] && i < (siz - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_src);
}
/*
int	main(void)
{
	char *s = NULL;
	size_t size = 3;
	// char d[size];
	char d2[size];

	// printf("retour: %ld, ft_strlcpy: %s.\n", ft_strlcpy(d, s, size), d);
	printf("retour: %ld, strlcpy: %s.\n", strlcpy(d2, s, size), d2);

	return (0);
}*/
