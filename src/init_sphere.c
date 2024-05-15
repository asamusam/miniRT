/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:25:57 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:26:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/scene.h"
#include "../includes/matrix.h"
#include "../includes/shapes.h"
#include "../includes/debug.h"

static void	sphere_transform(t_sphere *sphere, t_matrix *m)
{
	t_matrix	t;
	t_matrix	s;
	float		real_radius;

	m->size = 4;
	t.size = 4;
	s.size = 4;
	real_radius = sphere->diameter / 2;
	translation(sphere->center.x, sphere->center.y, sphere->center.z, &t);
	scaling(real_radius, real_radius, real_radius, &s);
	matrix_multiply(&t, &s, m);
}

void	calc_sphere(t_sphere *sphere, t_data *data)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	malloc_errcheck(object);
	object->type = SPHERE;
	sphere->default_radius = 1;
	sphere_transform(sphere, &object->transform);
	object->color = sphere->color;
	object->material = material();
	object->object = sphere;
	ft_lstadd_back(&data->scene->world.objects, ft_lstnew(object));
}
