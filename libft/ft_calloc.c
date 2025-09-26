/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:37:45 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/19 16:39:37 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*tab;
	unsigned char	*t;
	size_t			i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	tab = malloc(nmemb * size);
	if (tab == NULL)
		return (NULL);
	t = (unsigned char *)tab;
	i = 0;
	while (i < nmemb * size)
	{
		t[i] = 0;
		i++;
	}
	return (tab);
}
/*
int	main(void)
{
	size_t nmemb = 5;
	size_t size = 0;
	size_t i = 0;

	int *t1 = ft_calloc(nmemb, size);
	int *t2 = calloc(nmemb, size);

	if (t1 == NULL)
		printf("t1 vaut NULL\n");
	if (t2 == NULL)
		printf("t2 vaut NULL\n");
	while (i < nmemb)
	{
		printf("ft_calloc: %d || calloc: %d\n", t1[i], t2[i]);
		i++;
	}
	free(t1);
	free(t2);

	return (0);
}*/
