/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:41:20 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 13:56:07 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	tab = malloc((sizeof(char) * len) + 1);
	if (tab == NULL)
		return (NULL);
	ft_strlcpy(tab, s + start, len + 1);
	return (tab);
}
/*
int	main(void)
{
	// char s[] = "01234";
	char *d;

	size_t size = 18446744073709551615;
	d = ft_substr("hola", 0, size);

	printf("ft_substr:%s, len: %ld\n", d, strlen(d));

	free(d);

	return (0);
}*/
