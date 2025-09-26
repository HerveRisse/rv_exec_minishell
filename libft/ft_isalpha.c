/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:30:20 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/19 12:59:54 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	else
		return (0);
}
/*
int	main(int argc, char *argv[])
{
	if (argc < 2)
		return (1);

	printf("%c is alpha: %d\n", argv[1][0], ft_isalpha(argv[1][0]));
	printf("%c is alpha (vrai): %d\n", argv[1][0], isalpha(argv[1][0]));
	return (0);
}*/
