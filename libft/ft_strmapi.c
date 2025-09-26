/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:52:40 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/27 13:27:58 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

/*
static char	test(unsigned int index, char c)
{
	return (c + index);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*tab;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = f(i, s[i]);
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

	d = ft_strmapi(s, test);
	if (d == NULL)
		return (1);
	printf("ft_strmapi:%s, len: %ld\n", d, ft_strlen(d));

	free(d);

	return (0);
}*/
