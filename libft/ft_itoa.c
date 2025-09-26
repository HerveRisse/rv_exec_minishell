/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:07 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/20 11:51:34 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include <stdio.h>

static size_t	compute_len(long n)
{
	long	nb;
	size_t	len;

	if (n == 0)
		return (1);
	nb = n;
	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= (-1);
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static void	fill_tab(char *s, long nb, size_t index)
{
	if (nb < 0)
	{
		s[0] = '-';
		nb *= (-1);
	}
	if (nb < 10)
		s[index] = 48 + nb;
	else
	{
		fill_tab(s, nb / 10, index - 1);
		fill_tab(s, nb % 10, index);
	}
}

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	len;

	len = compute_len(n);
	tab = malloc((sizeof(char) * len) + 1);
	if (tab == NULL)
		return (NULL);
	fill_tab(tab, n, len - 1);
	tab[len] = '\0';
	return (tab);
}
/*
int	main(void)
{
	char *s;
	int nb = -2147483648;

	s = ft_itoa(nb);

	printf("s:%s\n", s);
	if (s[11] == '\0')
		printf("Il y a bien le caractere de fin.\n");
	free(s);

	return (0);
}*/
