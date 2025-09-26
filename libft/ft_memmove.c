/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:37 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 16:56:10 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dest == NULL && src == NULL && n)
		return (NULL);
	s = src;
	d = dest;
	if (src > dest)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	return (dest);
}
/*
int	main(void)
{
	char s[0xF0];
	char s2[0xF0];
	int size = 0xF0 - 0xF;

	ft_memmove(s2, s2 + 3, size);
	memmove(s, s + 3, size);

	printf("ft_memmove: %s\n", s);
	printf("memmove: %s\n", s2);

	return (0);
}*/
