/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:23:08 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 19:27:11 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * 	Description:
 * 	It deletes the content of a node.
 * 	And free the memory of the node.
 *
 * 	Return value;
 * 	None.
 */

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
	{
		del(lst -> content);
		lst->content = NULL;

	}
	del(lst);
}
