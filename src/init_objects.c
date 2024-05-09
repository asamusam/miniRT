/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/09 18:45:34 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generalized.h"
#define _USE_MATH_DEFINES

t_matrix	*plane_transform(t_plane *plane)
{
	t_matrix	*m;

	m = translation(plane->point.x, plane->point.y, plane->point.z);
	m = matrix_multiply(*m, *rotation_x(M_PI / 2));
	return (m);
}

void	init_sphere_objects(t_data *data)
{
	t_object	*object;
	t_sphere	*sphere;
	t_list		*i;

	i = data->scene->spheres;
	while (i)
	{
		sphere = (t_sphere *)i->content;
		object = malloc(sizeof(t_object));
		if (!object)
		{
			// free_memory
			return ;
		}
		object->type = SPHERE;
		sphere->radius = sphere->diameter / 2;
		object->transform = translation(
				sphere->center.x, sphere->center.y, sphere->center.z);
		object->color = sphere->color;
		object->material = sphere->material;
		object->object = i->content;
		i->content = object;
		i = i->next;
	}
	ft_lstadd_back(&data->scene->world.objects, data->scene->spheres);
	// memory needs to be freed in the end
}

void	init_plane_objects(t_data *data)
{
	t_object	*object;
	t_plane		*plane;
	t_list		*i;

	i = data->scene->planes;
	while (i)
	{
		plane = (t_plane *)i->content;
		object = malloc(sizeof(t_object));
		if (!object)
		{
			// free_memory
			return ;
		}
		object->type = PLANE;
		object->transform = plane_transform(plane);
		object->color = plane->color;
		object->material = material();
		object->object = i->content;
		i->content = object;
		i = i->next;
	}
	ft_lstadd_back(&data->scene->world.objects, data->scene->planes);
	// memory needs to be freed in the end
}

void	init_objects(t_data *data)
{
	init_plane_objects(data);
	//init_sphere_objects(data);
}
