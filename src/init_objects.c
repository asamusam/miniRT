/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/13 20:38:51 by llai             ###   ########.fr       */
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
	t_matrix	*t;
	t_matrix	*r;

	t = translation(plane->point.x, plane->point.y, plane->point.z);
	r = rotate_plane(plane);
	m = matrix_multiply(*t, *r);
	free_matrix(&t);
	free_matrix(&r);
	return (m);
}

static t_matrix	*sphere_transform(t_sphere *sphere)
{
	t_matrix	*m;
	t_matrix	*t;
	t_matrix	*s;
	float		radius;

	radius = sphere->diameter / 2;
	t = translation(sphere->center.x, sphere->center.y, sphere->center.z);
	s = scaling(radius, radius, radius);
	m = matrix_multiply(*t, *s);
	free_matrix(&t);
	free_matrix(&s);
	return (m);
}

static t_matrix	*rotate_cylinder(t_cylinder *cylinder)
{
	t_matrix	*m;
	float		angle;
	t_tuple		axis;
	float		c;
	float		s;

	m = init_identitymatrix(4);
	angle = acos(dot((t_tuple){0, 1, 0, VECTOR}, normalize(cylinder->axis)));
	if (angle == 0)
		return (m);
	axis = normalize(cross((t_tuple){0, 1, 0, VECTOR}, normalize(cylinder->axis)));
	s = sin(angle);
	c = cos(angle);
	m->data[0][0] = c + axis.x * axis.x * (1 - c);
    m->data[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
    m->data[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
    m->data[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
    m->data[1][1] = c + axis.y * axis.y * (1 - c);
    m->data[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
    m->data[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
    m->data[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
    m->data[2][2] = c + axis.z * axis.z * (1 - c);
	return (m);
}

static t_matrix	*cylinder_transform(t_cylinder *cylinder)
{
	t_matrix	*i;
	t_matrix	*t;
	t_matrix	*r;
	// t_matrix	*s;
	t_matrix	*m;
	// float		radius;
	//
	// radius = cylinder->diameter / 2;
	i = init_identitymatrix(4);
	t = translation(cylinder->center.x, cylinder->center.y, cylinder->center.z);
	r = rotate_cylinder(cylinder);
	// s = scaling(radius, radius, 1);
	// m = matrix_multiply(*i, *t);
	// m = matrix_multiply(*i, *s);
	// m = matrix_multiply(*m, *t);
	m = matrix_multiply(*t, *r);
	// m = matrix_multiply(*i, *t);
	free_matrix(&i);
	free_matrix(&t);
	free_matrix(&r);
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

void	calc_cylinder(t_cylinder *cylinder, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = CYLINDER;
	object->transform = cylinder_transform(cylinder);
	// object->transform = matrix_multiply(*init_identitymatrix(4), *rotation_x(M_PI / 3));
	// object->transform = init_identitymatrix(4);
	object->color = cylinder->color;
	object->material = material();
	cylinder->minimum = 0;
	cylinder->maximum = cylinder->height;
	cylinder->closed = true;
	object->object = cylinder;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
}
