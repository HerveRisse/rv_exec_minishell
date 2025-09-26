/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:32:16 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 17:46:45 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <bsd/string.h>
// #include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!little[0])
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && little[j])
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char big[] = "MZIRIBMZIRIBMZE123";
	char little[] = "MZIRIBMZE";
	size_t len = strlen(little);

	printf("len debug: %ld\n", len);
	char *d = ft_strnstr(big, little, len);
	// char *d2 = strnstr(big, little, len);
	printf("ft_strnstr: %s, len: %ld\n", d, strlen(d));
	// printf("strnstr: %s, len: %ld\n", d2, strlen(d2));

	return (0);
}*/
