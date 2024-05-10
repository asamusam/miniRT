/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/10 20:34:32 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/scene.h"
#include "../includes/matrix.h"
#include "../includes/shapes.h"
#include "../includes/debug.h"
#include <math.h>

static t_matrix	*rotate_plane(t_plane *plane)
{
	t_matrix	*m;
	float		angle;
	t_tuple		axis;
	float		c;
	float		s;

	m = init_identitymatrix(4);
	angle = acos(dot((t_tuple){0, 1, 0, VECTOR}, plane->normal));
	axis = normalize(cross((t_tuple){0, 1, 0, VECTOR}, plane->normal));
	s = sin(angle);
	c = cos(angle);
	m->data[0][0] = c + pow(axis.x, 2) * (1 - c);
	m->data[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
	m->data[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
	m->data[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
	m->data[1][1] = c + pow(axis.y, 2) * (1 - c);
	m->data[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
	m->data[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
	m->data[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
	m->data[2][2] = c + pow(axis.y, 2) * (1 - c);
	return (m);
}

static t_matrix	*plane_transform(t_plane *plane)
{
	t_matrix	*m;

	m = translation(plane->point.x, plane->point.y, plane->point.z);
	m = matrix_multiply(*m, *rotate_plane(plane));
	return (m);
}

static t_matrix	*sphere_transform(t_sphere *sphere)
{
	t_matrix	*m;
	float		radius;

	radius = sphere->diameter / 2;
	m = translation(sphere->center.x, sphere->center.y, sphere->center.z);
	m = matrix_multiply(*m, *scaling(radius, radius, radius));
	return (m);
}

void	calc_sphere(t_sphere *sphere, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = SPHERE;
	sphere->radius = 1;
	object->transform = sphere_transform(sphere);
	object->color = sphere->color;
	object->material = material();
	object->object = sphere;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
}

void	calc_plane(t_plane *plane, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = PLANE;
	object->transform = plane_transform(plane);
	object->color = plane->color;
	object->material = material();
	object->object = plane;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
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
		sphere->radius = 1;
		object->transform = sphere_transform(sphere);
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

