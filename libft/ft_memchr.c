/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:25:16 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 17:07:43 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return (p + i);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *src = "/|\x12\xff\x09\x42\2002\42|\\";
	int size = 10;

	char *d = ft_memchr(src, '\200', size);
	char *d2 = memchr(src, '\200', size);

	printf("ft_memchr: %s\n", d);
	printf("memchr: %s\n", d2);

	return (0);
}*/
