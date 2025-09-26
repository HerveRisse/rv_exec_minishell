/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:49:49 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 11:37:58 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <bsd/string.h>
// #include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	initial_len_dst;
	size_t	len_src;
	size_t	i;

	initial_len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = initial_len_dst;
	if (siz <= initial_len_dst)
		return (siz + len_src);
	while (*src && i < siz - 1)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	dst[i] = '\0';
	return (initial_len_dst + len_src);
}
/*
int	main(void)
{
	char	s[] = "abcdefghjildsfa;dklf;sf";
	size_t	size = 10;
	char	d[] = "test";
	char	d2[] = "test";
	
	printf("retour: %ld, ft_strlcat: %s\n", ft_strlcat(d, s, size), d);
	printf("retour: %ld, strlcat: %s\n", strlcat(d2, s, size), d2);

	return (0);
}*/
