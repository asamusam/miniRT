/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:27:05 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:27:39 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/scene.h"
#include "../includes/matrix.h"
#include "../includes/shapes.h"
#include "../includes/debug.h"
#include <math.h>

static void	rotate_plane(t_plane *plane, t_matrix *r)
{
	t_tuple		default_normal;
	t_tuple		axis;
	float		angle;
	float		c;
	float		s;

	init_identitymatrix(r);
	default_normal = vector(0, 1, 0);
	angle = acos(dot(default_normal, plane->normal));
	axis = normalize(cross(default_normal, plane->normal));
	s = sin(angle);
	c = cos(angle);
	r->data[0][0] = c + pow(axis.x, 2) * (1 - c);
	r->data[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
	r->data[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
	r->data[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
	r->data[1][1] = c + pow(axis.y, 2) * (1 - c);
	r->data[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
	r->data[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
	r->data[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
	r->data[2][2] = c + pow(axis.y, 2) * (1 - c);
}

static void	plane_transform(t_plane *plane, t_matrix *m)
{
	t_matrix	t;
	t_matrix	r;

	m->size = 4;
	t.size = 4;
	r.size = 4;
	translation(plane->point.x, plane->point.y, plane->point.z, &t);
	rotate_plane(plane, &r);
	matrix_multiply(&t, &r, m);
}

void	calc_plane(t_plane *plane, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = PLANE;
	plane_transform(plane, &object->transform);
	object->color = plane->color;
	object->material = material();
	object->object = plane;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
}
