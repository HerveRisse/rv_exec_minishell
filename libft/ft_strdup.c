/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:48:06 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/27 12:50:08 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"
// #include <stdio.h>

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	size;
	size_t	i;

	size = ft_strlen((s));
	tab = malloc((sizeof(char) * size) + 1);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
/*
int	main(void)
{
	char s[] = "";
	char *d;
	char *d2;

	d = ft_strdup(s);
	d2 = strdup(s);

	printf("ft_strdup: %s, len: %ld\n", d, ft_strlen(d));
	printf("strdup: %s, len: %ld\n", d2, ft_strlen(d2));
	
	free(d);
	free(d2);

	return (0);
}*/
