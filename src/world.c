/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 18:56:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include <stdlib.h>
#include <math.h>

t_world	world(void)
{
	t_world	world;

	world.spheres = NULL;
	world.light = point_light(point(0, 0, 0), color(0, 1, 1, 1));
	return (world);
}

t_world	default_world(void)
{
	t_world	new_world = world();

	// new_world.spheres
	// ft_lstadd_back(&new_world.spheres, ft_lstnew(sphere(point(0, 0, 0), 0.5)));
	new_world.obj_nb = 2;
	new_world.spheres = malloc(2 * sizeof(t_sphere));
	new_world.spheres[0] = sphere(point(0, 0, 0), 1);
	new_world.spheres[0].material.color = color(0, 0.8, 1, 0.6);
	new_world.spheres[0].material.diffuse = 0.7;
	new_world.spheres[0].material.specular = 0.2;
	new_world.spheres[1] = sphere(point(0, 0, 0), 1);
	new_world.spheres[1].transform = scaling(0.5, 0.5, 0.5);

	new_world.light = point_light(point(-10, 10, -10), color(0, 1, 1, 1));
	return (new_world);
}

void	insertion_sortlist(t_list **head)
{
	t_list *sorted = NULL;
    t_list *current = *head;

    while (current != NULL)
    {
        t_list *next = current->next;

        // Find the correct position to insert current in the sorted list
        if (sorted == NULL || *(double *)sorted->content >= *(double *)current->content)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            t_list *temp = sorted;
            while (temp->next != NULL && *(double *)temp->next->content < *(double *)current->content)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    // Update head_ref to point to the sorted list
    *head = sorted;
}

t_list *intersect_world(t_world world, t_ray ray)
{
	t_list	*result = NULL;
	int	i = -1;

	while (++i < world.obj_nb)
	{
		ft_lstadd_back(&result,	intersect(world.spheres[i], ray));
	}
	insertion_sortlist(&result);
	return (result);
}

t_comps	prepare_computations(t_intersection intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection.t;
	comps.sphere = intersection.object;
	comps.point = position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.sphere, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	return (lighting(comps.sphere.material, world.light, comps.point, comps.eyev, comps.normalv));
}

t_color	color_at(t_world world, t_ray ray)
{
	t_list *intersections;
	intersections = intersect_world(world, ray);
	t_intersection	*i = hit(intersections);
	if (i == NULL)
		return (color(0, 0, 0, 0));
	t_comps comps = prepare_computations(*i, ray);
	t_color	color = shade_hit(world, comps);
	return (color);
}
