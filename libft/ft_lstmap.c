/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sm-gaidi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:05:27 by sm-gaidi          #+#    #+#             */
/*   Updated: 2024/11/23 12:40:25 by sm-gaidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_element;
	t_list	*temp;

	new_lst = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (new_element == NULL)
		{
			ft_lstclear(&new_element, del);
			return (NULL);
		}
		if (new_lst == NULL)
			new_lst = new_element;
		else
		{
			temp = ft_lstlast(new_lst);
			temp->next = new_element;
		}
		lst = lst->next;
	}
	return (new_lst);
}
