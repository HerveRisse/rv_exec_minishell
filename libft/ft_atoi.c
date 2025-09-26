/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saif-eddine <saif-eddine@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:07 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/05/27 14:06:51 by saif-eddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
// #include <stdio.h>

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\n' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *nptr)
{
	long	nb;
	int		sign;
	int		i;

	nb = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb *= 10;
		nb += (nptr[i] - 48);
		i++;
	}
	return (nb * sign);
}
/*
int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	printf("ft_atoi: %d\n", ft_atoi(argv[1]));
	printf("atoi: %d\n", atoi(argv[1]));

	return (0);
}*/
