/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/08 18:14:40 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generalized.h"

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
	t_matrix 	*m;

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
		m = init_identitymatrix(4);
		m->data[0][0] = 0.0;
		m->data[0][1] = -1.0;
		m->data[0][3] = 1.0;
		m->data[1][0] = 1.0;
		m->data[1][1] = 0.0;
		m->data[2][3] = 2.0;
		object->type = PLANE;
		object->transform = m;
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
	//init_sphere_objects(data);
	init_plane_objects(data);
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

