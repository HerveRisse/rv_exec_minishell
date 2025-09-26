/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:55:20 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 14:12:21 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
/*
static void	test(unsigned int index, char *c)
{
	*c += index;
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, (s + i));
		i++;
	}
}
/*
int	main(void)
{
	char s[] = "abcd";

	printf("s:%s\n", s);

	ft_striteri(s, test);

	printf("s:%s\n", s);

	return (0);
}*/
