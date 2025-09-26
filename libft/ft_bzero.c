/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:00:22 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 14:07:06 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
// #include <stdio.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}
/*
int	main(void)
{
	char *m = NULL;
	char *t = NULL;
	size_t n = 4;

	ft_bzero(m, n);
	bzero(t, n);

	printf("ft_bzero: %s\n", m);
	printf("bzero: %s\n", t);
	return (0);
}*/
