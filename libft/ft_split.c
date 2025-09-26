/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:48:56 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 16:36:28 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	flag;
	size_t	i;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != (unsigned char)c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (s[i] == (unsigned char)c && flag == 1)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*get_word(const char **s, unsigned char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (**s == c)
		(*s)++;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	word = ft_substr(*s, 0, i);
	(*s) += i;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words_count;
	size_t	i;

	words_count = count_words(s, c);
	tab = malloc(sizeof(char *) * (words_count + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < words_count)
	{
		tab[i] = get_word(&s, c);
		if (tab[i] == NULL)
		{
			while (i > 0)
				free(tab[--i]);
			free(tab);
			return (NULL);
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
/*
int	main(int argc, char *argv[])
{
	char **tab;
	size_t i;

	if (argc != 3)
		return (1);
	tab = ft_split(argv[1], argv[2][0]);
	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab[%ld] = %s\n", i, tab[i]);
		i++;
	}
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
	return (0);
}*/
