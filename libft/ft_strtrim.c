/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:45:51 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 14:21:10 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"
// #include <stdio.h>

static int	in_set(char const *set, int c)
{
	unsigned char	ch;
	size_t			i;

	ch = c;
	i = 0;
	while (set[i])
	{
		if (set[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

static void	fill_tab(char *tab, const char *s1, size_t start, size_t end)
{
	size_t	i;

	i = 0;
	while (i <= (end - start))
	{
		tab[i] = s1[start + i];
		i++;
	}
	tab[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tab;
	int		size;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = 0;
	if (ft_strlen(s1) > 0)
		end = ft_strlen(s1) - 1;
	else
		return (ft_strdup(""));
	while (s1[start] && in_set(set, s1[start]))
		start++;
	while (end >= 0 && in_set(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	size = (end - start) + 1;
	tab = malloc((sizeof(char) * size) + 1);
	if (tab == NULL)
		return (NULL);
	fill_tab(tab, s1, start, end);
	return (tab);
}
/*
int	main(void)
{
	char s[] = "";
	char set[] = " as";
	char *d;

	d = ft_strtrim(s, set);
	if (d == NULL)
		printf("d vaut NULL\n");
	printf("ft_strtrim:%s, len: %ld\n", d, strlen(d));

	free(d);

	return (0);
}*/
