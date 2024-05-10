/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:22:41 by llai              #+#    #+#             */
/*   Updated: 2024/05/10 19:04:55 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/light.h"
#include "../includes/shapes.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include "../includes/minirt.h"
#include <math.h>

t_light	point_light(t_tuple position, float intensity, t_color color)
{
	return ((t_light){position, intensity, color});
}

t_material	material(void)
{
	t_material	m;

	m.color = color(0, 1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}

// t_color	compute_ambient(t_comps c, t_color effective_color)
t_color	compute_ambient(t_world w, t_color effective_color)
{
	return (hadamard_product(effective_color, mul_color(
				w.ambient.color, w.ambient.intensity)));
}

// A negative number means the light is on the other side of the surface
t_color	compute_diffuse(t_shape_comps *c, t_color eff_color, t_light light)
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

// A negative number means the light reflects away from the eye.
t_color	compute_specular(t_shape_comps *c, t_light light)
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

// First it finds the surface color with light's color 
// then it adds up with ambient, diffuse and specular.
t_color	lighting(t_world *w, t_shape_comps *c, bool in_shadow)
{
	t_color	effective_color;
	t_color	ambient;
	t_color	diffuse;
	t_color	specular;

	effective_color = hadamard_product(c->object->color, w->light.color);
	ambient = hadamard_product(
			effective_color, mul_color(w->ambient.color, w->ambient.intensity));
	diffuse = compute_diffuse(c, effective_color, w->light);
	specular = compute_specular(c, w->light);
	if (in_shadow)
		return (ambient);
	return (add_colors(ambient, mul_color(
				add_colors(diffuse, specular), w->light.intensity)));
}

bool	is_shadowed(t_world world, t_tuple point)
{
	t_shadow			shadow;
	t_ray				r;
	t_list				*intersections;
	t_shape_intersect	*h;

	shadow.v = sub_tuples(world.light.position, point);
	shadow.distance = magnitude(shadow.v);
	shadow.direction = normalize(shadow.v);
	r = ray(point, shadow.direction);
	intersections = intersect_world(world, r);
	h = hit(intersections);
	if (h && h->t < shadow.distance)
	{
		ft_lstclear(&intersections, free);
		return (true);
	}
	else
	{
		ft_lstclear(&intersections, free);
		return (false);
	}
}
