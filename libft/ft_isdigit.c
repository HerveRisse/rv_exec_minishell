/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:57:18 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/19 13:01:54 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}
/*
int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	printf("%c ft_isdigit: %d\n", argv[1][0], ft_isdigit(argv[1][0]));
	printf("%c isdigit: %d\n", argv[1][0], isdigit(argv[1][0]));
	return (0);
}*/
