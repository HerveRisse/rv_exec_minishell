/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:41:27 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/12 14:28:47 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*
int	main(void)
{
	int	c;

	c = 127;
	printf("ft_isprint: %d\n", ft_isprint(c));
	printf("ft_isprint: %d\n", isprint(c));
	return (0);
}*/
