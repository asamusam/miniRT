/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/08 21:58:28 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generalized.h"

t_matrix	*plane_transform(t_plane *plane)
{
	t_matrix	*m;
	t_tuple		random;
	t_tuple		project;
	t_tuple		x_axis;
	t_tuple		y_axis;

	m = init_identitymatrix(4);
	m->data[0][2] = plane->normal.x;
	m->data[1][2] = plane->normal.y;
	m->data[2][2] = plane->normal.z;
	random.x = 1.0;
	random.y = 2.0;
	random.z = 3.0;
	random.w = VECTOR;
	project = sub_tuples(random, scalar_mul_tuple(
				dot(random, plane->normal), plane->normal));
	x_axis = normalize(cross(plane->normal, project));
	y_axis = normalize(cross(x_axis, plane->normal));
	m->data[0][0] = x_axis.x;
	m->data[1][0] = x_axis.y;
	m->data[2][0] = x_axis.z;
	m->data[0][1] = y_axis.x;
	m->data[1][1] = y_axis.y;
	m->data[2][1] = y_axis.z;
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
		//object->transform = translation(
		//		plane->point.x, plane->point.y, plane->point.z);
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
	init_sphere_objects(data);
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
	//ft_lstadd_back(&data->scene->world.objects, data->scene->planes);
	//ft_lstadd_back(&data->scene->world.objects, data->scene->cylinders);
	// memory needs to be freed in the end

