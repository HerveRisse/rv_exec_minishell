/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:43:56 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/27 13:26:17 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;

	tab = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
	{
		tab[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	tab[i] = '\0';
	return (tab);
}
/*
int	main(void)
{
	char s1[] = "Saif,";
	char s2[] = " va reussir dans l'intelligence artificielle !";
	char *d;

	d = ft_strjoin(s1, s2);
	if (d == NULL)
		return (1);
	printf("ft_strjoin: %s, len: %ld\n", d, ft_strlen(d));

	return (0);
}*/
