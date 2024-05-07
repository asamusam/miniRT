/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalized.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:30:22 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/07 18:34:16 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "generalized.h"


int	calc_t(t_sphere s, t_ray ray, float *t1, float *t2);

// sphere_intersect
t_list	*sphere_intersect(t_sphere *s, t_ray ray)
{
	t_list	*interections_list;
	float	t1;
	float	t2;

	ray = transform(ray, inverse(s->transform));
	interections_list = NULL;
	if (calc_t(*s, ray, &t1, &t2) == -1)
		return (interections_list);
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t1, *s)));
	ft_lstadd_back(&interections_list, ft_lstnew(intersection(t2, *s)));
	return (interections_list);
}

// common intersect
t_list	*shape_intersect(t_object *obj, t_ray ray)
{
	t_list	*intersections;

	if (obj->type == SPHERE)
		intersections = sphere_intersect(obj->object, ray);
	return (intersections);
}

void	transform_object(void *content)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_object	*object;

	object = (t_object *)content;
	if (object->type == SPHERE)
	{
		sphere = content;
		sphere->radius = sphere->diameter / 2;
		sphere->transform = translation(
				sphere->center.x, sphere->center.y, sphere->center.z);
	}
	else if (object->type == PLANE)
	{
		plane = content;
		plane->material = material();
		plane->transform = translation(
				plane->point.x, plane->point.y, plane->point.z);
	}
}

void	init_objects(t_data *data)
{
	t_object	*object;
	t_list		*i;

	i = data->scene->spheres;
	while (i)
	{
		object = malloc(sizeof(t_object));
		if (!object)
		{
			// free_memory
			return ;
		}
		object->type = SPHERE;
		object->object = i->content;
		i->content = object;
		i = i->next;
	}
	// i = data->scene->planes;
	// while (i)
	// {
	// 	object = malloc(sizeof(t_object));
	// 	if (!object)
	// 	{
	// 		// free_memory
	// 		return ;
	// 	}
	// 	object->type = PLANE;
	// 	object->object = i->content;
	// 	i->content = object;
	// 	i = i->next;
	// }
	// i = data->scene->cylinders;
	// while (i)
	// {
	// 	object = malloc(sizeof(t_object));
	// 	if (!object)
	// 	{
	// 		// free_memory
	// 		return ;
	// 	}
	// 	object->type = CYLINDER;
	// 	object->object = i->content;
	// 	i->content = object;
	// 	i = i->next;
	// }
	ft_lstadd_back(&data->scene->world.objects, data->scene->spheres);
	//ft_lstadd_back(&data->scene->world.objects, data->scene->planes);
	//ft_lstadd_back(&data->scene->world.objects, data->scene->cylinders);
	ft_lstiter(data->scene->world.objects, transform_object);
	// memory needs to be freed in the end
}
