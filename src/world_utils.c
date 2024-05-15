/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:17:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include "../includes/world.h"
#include "../includes/scene.h"
#include <stdbool.h>
#include <stdio.h>

void	insert_sorted(t_list **sorted, t_list *node)
{
	t_list	*temp;

	if (*sorted == NULL
		|| *(float *)(*sorted)->content >= *(float *)node->content)
	{
		node->next = *sorted;
		*sorted = node;
	}
	else
	{
		temp = *sorted;
		while (temp->next != NULL
			&& *(float *)temp->next->content < *(float *)node->content)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
}

void	insertion_sortlist(t_list **head)
{
	t_list	*sorted;
	t_list	*current;

	sorted = NULL;
	while (*head != NULL)
	{
		current = *head;
		*head = current->next;
		insert_sorted(&sorted, current);
	}
	*head = sorted;
}

t_list	*intersect_world(t_world *world, t_ray *ray)
{
	t_list	*result;
	t_list	*tmp;

	result = NULL;
	tmp = world->objects;
	while (tmp)
	{
		ft_lstadd_back(&result, intersect(tmp->content, ray));
		tmp = tmp->next;
	}
	insertion_sortlist(&result);
	return (result);
}

// It precomputes the point in the world space where the intersection 
// occurred, the eye veector, and the normal vector
void	prepare_comps(
	t_shape_intersect *intersect, t_ray *ray, t_shape_comps *comps)
{
	comps->t = intersect->t;
	comps->object = intersect->object;
	comps->point = position(*ray, comps->t);
	comps->eyev = negate_tuple(ray->direction);
	comps->normalv = normal_at(intersect->object, comps->point);
	comps->over_point = add_tuples(comps->point,
			scalar_mul_tuple(EPSILON, comps->normalv));
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = true;
		comps->normalv = negate_tuple(comps->normalv);
	}
	else
		comps->inside = false;
}
