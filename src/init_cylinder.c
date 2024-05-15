/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:22:26 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/15 14:16:01 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/scene.h"
#include "../includes/matrix.h"
#include "../includes/shapes.h"
#include "../includes/debug.h"
#include <math.h>

void	rotate_cylinder(t_cylinder *cylinder, t_matrix *r)
{
	t_tuple		default_normal;
	float		angle;
	t_tuple		axis;
	float		c;
	float		s;

	init_identitymatrix(r);
	default_normal = vector(0, 1, 0);
	angle = acos(dot(default_normal, normalize(cylinder->axis)));
	axis = normalize(cross(default_normal, normalize(cylinder->axis)));
	if (fabs(angle) < EPSILON)
		return ;
	s = sin(angle);
	c = cos(angle);
	r->data[0][0] = c + axis.x * axis.x * (1 - c);
	r->data[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
	r->data[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
	r->data[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
	r->data[1][1] = c + axis.y * axis.y * (1 - c);
	r->data[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
	r->data[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
	r->data[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
	r->data[2][2] = c + axis.z * axis.z * (1 - c);
}

void	cylinder_transform(t_cylinder *cylinder, t_matrix *m)
{
	t_matrix	t;
	t_matrix	s;
	t_matrix	ts;
	t_matrix	r;
	float		real_radius;

	m->size = 4;
	t.size = 4;
	s.size = 4;
	ts.size = 4;
	r.size = 4;
	real_radius = cylinder->diameter / 2;
	translation(cylinder->center.x, cylinder->center.y, cylinder->center.z, &t);
	scaling(real_radius, 1, real_radius, &s);
	rotate_cylinder(cylinder, &r);
	matrix_multiply(&t, &s, &ts);
	matrix_multiply(&ts, &r, m);
}

void	calc_cylinder(t_cylinder *cylinder, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = CYLINDER;
	cylinder_transform(cylinder, &object->transform);
	object->color = cylinder->color;
	object->material = material();
	cylinder->minimum = 0 - cylinder->height /2;
	cylinder->maximum = cylinder->height / 2;
	cylinder->closed = true;
	object->object = cylinder;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
}
