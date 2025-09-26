/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:30:42 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 14:11:32 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	size_t			i;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if ((p1[i] > p2[i]) || (p1[i] < p2[i]))
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	// char s1[] = "test";
	// char s2[] = "test";
	// int s1[] = {1, 2, 3, 4};
	// int s2[] = {1, 2, 3, 10};
	size_t n = 16;

	printf("ft_memcmp: %d\n", ft_memcmp(s1, s2, n));
	printf("memcmp: %d\n", memcmp(s1, s2, n));

	return (0);
}*/
