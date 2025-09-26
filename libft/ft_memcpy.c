/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:28 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 15:17:44 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == NULL && src == NULL && n)
		return (NULL);
	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	const char *s = NULL;
	char *d = NULL;
	char *d2 = NULL;
	size_t n = 10;

	ft_memcpy(d, s, n);
	memcpy(d2, s, n);

	printf("ft_memcpy: %s\n", d);
	printf("memcpy: %s\n", d2);

	return (0);
}*/
