/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:49:31 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/03/12 12:49:35 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_len(const char *s, int c)
{
	size_t	i;

	if (s == NULL || *s == '\0')
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (i);
}

char	*str_joined(const char *s1, const char *s2, size_t len_1, size_t len_2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!len_1 && !len_2)
		return (NULL);
	joined = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (joined == NULL)
		return (NULL);
	i = 0;
	while (i < len_1)
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_2)
	{
		joined[i + j] = s2[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*find_ch(char *remainder, int c)
{
	size_t	i;

	if (remainder == NULL)
		return (NULL);
	i = 0;
	while (remainder[i])
	{
		if (remainder[i] == c)
			return (remainder + i);
		i++;
	}
	return (NULL);
}

char	*get_new_line(char *remainder)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (remainder == NULL)
		return (NULL);
	len = get_len(remainder, '\n');
	if (len == 0)
		return (NULL);
	line = malloc(sizeof(char) * len + 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = remainder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_remainder(char **remainder, size_t start)
{
	char	*new;
	size_t	size;
	size_t	j;

	if (*remainder == NULL)
		return (NULL);
	size = get_len(*remainder, 0);
	if (start >= size)
	{
		free(*remainder);
		return (NULL);
	}
	j = 0;
	new = malloc(sizeof(char) * (size - start) + 1);
	if (new == NULL)
		return (NULL);
	while ((*remainder)[start])
	{
		new[j] = (*remainder)[start];
		start++;
		j++;
	}
	new[j] = '\0';
	free(*remainder);
	return (new);
}
