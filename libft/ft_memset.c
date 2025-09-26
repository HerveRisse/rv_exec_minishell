/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saif-eddine <saif-eddine@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:44:08 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/05/21 22:44:50 by saif-eddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char s[] = "Test";
	int c = 97;
	size_t n = 8;
	char *m = ft_memset(s, c, n);
	char *t = memset(s, c, n);
	printf("ft_memset: %s\n", m);
	printf("memset: %s\n", t);
	return (0);
}*/
