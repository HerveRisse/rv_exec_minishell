/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:22:06 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 12:47:39 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	unsigned char	ch;
	char			*last_occ;

	last_occ = NULL;
	ch = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			last_occ = (char *)(s + i);
		i++;
	}
	if (ch == '\0')
		last_occ = (char *)(s + i);
	return (last_occ);
}
/*
int	main(void)
{
	char s[] = "abcdca";
	int c = 'c';

	printf("ft_strrchr: %s\n", ft_strrchr(s, c));
	printf("strrchr: %s\n", strrchr(s, c));

	return (0);
}*/
