/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:11:48 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/21 18:12:19 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
int	main(void)
{
	t_list	*list;
	// char	s[] = "saif";

	list = ft_lstnew("0");
	char *d = list->content;

	printf("%s\n", d);
	if (list->next == NULL)
		printf("next: NULL\n");
	return (0);
}*/
