/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saif-eddine <saif-eddine@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:48:55 by sm-gaidi          #+#    #+#             */
/*   Updated: 2025/05/21 22:38:43 by saif-eddine      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_buffer(char *buffer)
{
	size_t	i;

	if (buffer == NULL)
		return ;
	i = 0;
	while (buffer[i])
	{
		buffer[i] = 0;
		i++;
	}
}

int	check_endfile(int read_bytes, char buffer[BUFFER_SIZE], char **remainder)
{
	if (read_bytes <= 0)
	{
		clear_buffer(buffer);
		if (read_bytes < 0)
		{
			free(*remainder);
			*remainder = NULL;
			return (2);
		}
		return (1);
	}
	return (0);
}

char	*read_file(int fd, char **remainder)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_line;
	char		*tmp;
	int			read_bytes;
	size_t		len_remainder;

	len_remainder = get_len(*remainder, 0);
	new_line = find_ch(*remainder, '\n');
	while (new_line == NULL)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (check_endfile(read_bytes, buffer, remainder))
			break ;
		buffer[read_bytes] = '\0';
		tmp = str_joined(*remainder, buffer, len_remainder, read_bytes);
		if (tmp == NULL)
			return (NULL);
		free(*remainder);
		*remainder = tmp;
		len_remainder += read_bytes;
		new_line = find_ch(*remainder, '\n');
	}
	return (new_line);
}

char	*get_next_line(int fd, int finish)
{
	static char	*remainder = NULL;
	char		*new_line;

	if (finish)
	{
		if (remainder)
		{
			free(remainder);
			remainder = NULL;
		}
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = read_file(fd, &remainder);
	new_line = get_new_line(remainder);
	remainder = new_remainder(&remainder, get_len(new_line, 0));
	return (new_line);
}
/*
int	main(void)
{
	char	*line;

	int fd = open("nl", O_RDONLY);
	if (fd < 0)
	{
		printf("Erreur lors de l'ouverture du fichier.\n");
		return (-1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line: %s", line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}*/

/*
Etapes:

1 - Lire les donnees avec read
2 - Chercher une nouvelle ligne
3 - Extraire la ligne
4 - Mettre a jour le reste non consommees
5 - retourner la ligne


*/
