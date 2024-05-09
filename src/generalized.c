/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalized.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:30:22 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/09 18:39:29 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/generalized.h"

int		calc_t(t_sphere s, t_ray ray, float *t1, float *t2);
t_color	compute_diffuse(t_comps c, t_color effective_color, t_light light);
void	malloc_errcheck(void *p);


t_color	shape_specular(t_shape_comps *c, t_light light)
{
	t_tuple	lightv;
	t_tuple	reflectv;
	float	reflect_dot_eye;
	float	factor;

	lightv = normalize(sub_tuples(light.position, c->point));
	reflectv = reflect(negate_tuple(lightv), c->normalv);
	reflect_dot_eye = dot(reflectv, c->eyev);
	if (reflect_dot_eye <= 0)
		return (color(0, 0, 0, 0));
	else
	{
		factor = pow(reflect_dot_eye, c->object->material.shininess);
		return (mul_color(mul_color(
					light.color, c->object->material.specular), factor * 255));
	}
}

t_color	shape_diffuse(t_shape_comps *c, t_color eff_color, t_light light)
{
	t_tuple	lightv;
	float	light_dot_normal;

	lightv = normalize(sub_tuples(light.position, c->point));
	light_dot_normal = dot(lightv, c->normalv);
	if (light_dot_normal < 0)
		return (color(0, 0, 0, 0));
	else
		return (mul_color(mul_color(
					eff_color, c->object->material.diffuse),
				light_dot_normal));
}


t_tuple	local_normal_at(t_object *object, t_tuple local_point)
{
	t_tuple normal;
	
	if (object->type == SPHERE)
		normal = sub_tuples(local_point, point(0, 0, 0));
	else if (object->type == PLANE)
		normal = (t_tuple){0, 1, 0, VECTOR};
	return (normalize(normal));
}

t_tuple	shape_normal_at(t_object *object, t_tuple world_pt)
{
	t_tuple		object_pt;
	t_tuple		object_normal;
	t_tuple		world_normal;
	t_matrix	*inv_m;
	t_matrix	*trans_m;

	inv_m = inverse(*object->transform);
	object_pt = matrix_tuple_multiply(*inv_m, world_pt);
	object_normal = local_normal_at(object, object_pt);
	trans_m = transpose(*inv_m);
	world_normal = matrix_tuple_multiply(
			*trans_m, object_normal);
	world_normal.w = 0;
	free_matrix(inv_m);
	free_matrix(trans_m);
	return (normalize(world_normal));
}

t_shape_comps	prepare_shape_comps(t_shape_intersect *intersect, t_ray *ray)
{
	t_shape_comps	comps;

	comps.t = intersect->t;
	comps.object = intersect->object;
	comps.point = position(*ray, comps.t);
	comps.eyev = negate_tuple(ray->direction);
	comps.normalv = shape_normal_at(intersect->object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_shape_intersect	*shape_intersection(float t, t_object *object)
{
	t_shape_intersect	*i;

	i = malloc(sizeof(t_shape_intersect));
	malloc_errcheck(i);
	i->t = t;
	i->object = object;
	return (i);
}


// common intersect
t_list	*shape_intersect(t_object *object, t_ray ray)
{
	t_list		*intersections;
	t_matrix	*inv_m;
	float		t1;
	float		t2;
	t_sphere	*sphere;

	inv_m = inverse(*object->transform);
	ray = transform(ray, *inv_m);
	free_matrix(inv_m);
	intersections = NULL;
	if (object->type == SPHERE)
	{
		sphere = (t_sphere *)object->object;
		if (calc_t(*sphere, ray, &t1, &t2) == -1)
			return (intersections);
		ft_lstadd_back(&intersections, ft_lstnew(
				shape_intersection(t1, object)));
		ft_lstadd_back(&intersections, ft_lstnew(
				shape_intersection(t2, object)));
	}
	else if (object->type == PLANE)
	{
		if (fabs(ray.direction.y) < EPSILON)
			return (intersections);
		t1 = -ray.origin.y / ray.direction.y;
		ft_lstadd_back(&intersections, ft_lstnew(
				shape_intersection(t1, object)));
	}
	return (intersections);
}

t_color	shape_lighting(t_world *w, t_shape_comps *c)
{
	t_color	effective_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	effective_color = hadamard_product(c->object->color, w->light.color);
	ambient = hadamard_product(
			effective_color, mul_color(w->ambient.color, w->ambient.intensity));
	diffuse = shape_diffuse(c, effective_color, w->light);
	specular = shape_specular(c, w->light);
	return (add_colors(ambient, mul_color(
				add_colors(diffuse, specular), w->light.intensity)));
}

t_shape_intersect	*shape_hit(t_list *xs)
{
	t_shape_intersect	*res;
	t_shape_intersect	*content;

	res = NULL;
	while (xs)
	{
		content = xs->content;
		if (res == NULL)
		{
			if (content->t > 0)
				res = content;
		}
		else
		{
			if (content->t > 0 && content->t < res->t)
				res = content;
		}
		xs = xs->next;
	}
	return (res);
}

t_color	shape_color_at(t_world world, t_ray ray)
{
	t_list				*intersections;
	t_shape_intersect	*i;
	t_shape_comps		comps;
	t_color				c;

	intersections = intersect_world(world, ray);
	i = shape_hit(intersections);
	if (i == NULL)
		return (color(0, 0, 0, 0));
	comps = prepare_shape_comps(i, &ray);
	c = shape_lighting(&world, &comps);
	return (c);
}