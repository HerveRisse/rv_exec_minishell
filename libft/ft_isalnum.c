/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:42 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/12 13:25:09 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>

int	ft_isalnum(int c)
{
	if (c >= 65 && c <= 90)
		return (8);
	else if (c >= 97 && c <= 122)
		return (8);
	else if (c >= 48 && c <= 57)
		return (8);
	else
		return (0);
}
/*
int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);
	printf("%c ft_isalnum: %d\n", argv[1][0], ft_isalnum(argv[1][0]));
	printf("%c isalnum: %d\n", argv[1][0], isalnum(argv[1][0]));
	return (0);
}*/
