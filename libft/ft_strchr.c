/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:20:06 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 12:47:13 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ch;
	unsigned int	i;

	ch = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i++;
	}
	if (ch == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
int	main(void)
{
	char s[] = "test";
	int c = 'b' + 256;

	printf("ft_strchr: %s\n", ft_strchr(s, c));
	printf("strchr: %s\n", strchr(s, c));
	
	return (0);
}*/
