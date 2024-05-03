/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:09:49 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 12:48:26 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * 	Description:
 * 	It finds the last node in the list.
 *
 * 	Return value;
 * 	The last node.
 */

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst != NULL && lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}
