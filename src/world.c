/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/05 02:21:36 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../libft/libft.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_world	world(void)
{
	t_world	world;

	world.objects = NULL;
	world.light = point_light(point(0, 0, 0), 1, color(0, 1, 1, 1));
	return (world);
}

t_world	default_world(void)
{
	t_world	new_world;

	new_world = world();
	new_world.light = point_light(point(-10, 10, -10), 1, color(0, 1, 1, 1));
	return (new_world);
}

void	insert_sorted(t_list **sorted, t_list *node)
{
	t_list	*temp;

	if (*sorted == NULL
		|| *(float *)(*sorted)->content >= *(float *)node->content)
	{
		node->next = *sorted;
		*sorted = node;
	}
	else
	{
		temp = *sorted;
		while (temp->next != NULL
			&& *(float *)temp->next->content < *(float *)node->content)
			temp = temp->next;
		node->next = temp->next;
		temp->next = node;
	}
}

void	insertion_sortlist(t_list **head)
{
	t_list	*sorted;
	t_list	*current;

	sorted = NULL;
	while (*head != NULL)
	{
		current = *head;
		*head = current->next;
		insert_sorted(&sorted, current);
	}
	*head = sorted;
}

t_list	*intersect_world(t_world world, t_ray ray)
{
	t_list	*result;
	t_list	*tmp;

	result = NULL;
	tmp = world.objects;
	while (tmp)
	{
		ft_lstadd_back(&result, intersect(*(t_sphere *)tmp->content, ray));
		tmp = tmp->next;
	}
	insertion_sortlist(&result);
	return (result);
}

// It precomputes the point in the world space where the intersection 
// occurred, the eye veector, and the normal vector
t_comps	prepare_computations(t_intersection intersection, t_ray ray)
{
	t_comps	comps;

	comps.t = intersection.t;
	comps.sphere = intersection.object;
	comps.point = position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.sphere, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	return (lighting(world, comps));
}

t_color	color_at(t_world world, t_ray ray)
{
	t_list			*intersections;
	t_intersection	*i;
	t_comps			comps;
	t_color			c;

	intersections = intersect_world(world, ray);
	i = hit(intersections);
	if (i == NULL)
		return (color(0, 0, 0, 0));
	comps = prepare_computations(*i, ray);
	c = shade_hit(world, comps);
	return (c);
}

t_matrix	make_orientation(t_tuple left, t_tuple true_up, t_tuple forword)
{
	t_matrix	orientation;

	orientation = create_matrix(4, 4);
	orientation.data[0][0] = left.x;
	orientation.data[0][1] = left.y;
	orientation.data[0][2] = left.z;
	orientation.data[0][3] = 0;
	orientation.data[1][0] = true_up.x;
	orientation.data[1][1] = true_up.y;
	orientation.data[1][2] = true_up.z;
	orientation.data[1][3] = 0;
	orientation.data[2][0] = -forword.x;
	orientation.data[2][1] = -forword.y;
	orientation.data[2][2] = -forword.z;
	orientation.data[2][3] = 0;
	orientation.data[3][0] = 0;
	orientation.data[3][1] = 0;
	orientation.data[3][2] = 0;
	orientation.data[3][3] = 1;
	return (orientation);
}

// It mimics the eye/camera moves instead of the world
// from where the eye in the scene
// to where you want to look at
// and a vector indicates which direction is up
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forword;
	t_tuple		upn;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	orientation;

	forword = normalize(sub_tuples(to, from));
	upn = normalize(up);
	left = cross(forword, upn);
	true_up = cross(left, forword);
	orientation = make_orientation(left, true_up, forword);
	return (matrix_multiply(orientation,
			translation(-from.x, -from.y, -from.z)));
}

t_cam	camera(float hsize, float vsize, float field_of_view)
{
	t_cam		c;
	float		half_view;
	float		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.rfov = field_of_view;
	c.transform = init_identitymatrix(4);
	half_view = tan(c.rfov / 2);
	aspect = c.hsize / c.vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}

// The camera pixel size is calculated with the horizontal aspect
// and vertical aspect
// t_camera	camera(float hsize, float vsize, float field_of_view)
void	configure_camera(t_cam *c)
{
	float		half_view;
	float		aspect;

	c->hsize = WIDTH;
	c->vsize = HEIGHT;
	c->rfov = radians(c->fov);
	c->transform = init_identitymatrix(4);
	half_view = tan(c->rfov / 2);
	aspect = c->hsize / c->vsize;
	if (aspect >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect;
	}
	else
	{
		c->half_width = half_view * aspect;
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
}

float	calc_offset(t_cam camera, float p)
{
	return ((p + 0.5) * camera.pixel_size);
}

// It returns new ray from the camera and passes through 
// the indicated (x, y) pixel on the canvas
t_ray	ray_for_pixel(t_cam camera, float px, float py)
{
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	world_x = camera.half_width - calc_offset(camera, px);
	world_y = camera.half_height - calc_offset(camera, py);
	pixel = matrix_tuple_multiply(
			inverse(camera.transform), point(world_x, world_y, -1));
	origin = matrix_tuple_multiply(
			inverse(camera.transform), point(0, 0, 0));
	direction = normalize(sub_tuples(pixel, origin));
	return (ray(origin, direction));
}

void	render(t_data *data, t_cam camera, t_world world)
{
	t_ray	r;
	t_color	color;
	int		x;
	int		y;

	y = -1;
	while (++y < camera.vsize)
	{
		x = -1;
		while (++x < camera.hsize)
		{
			r = ray_for_pixel(camera, x, y);
			color = color_at(world, r);
			put_pixel2(data->base_image, x, y, color);
		}
	}
	mlx_put_image_to_window(data->base_image->mlx,
		data->base_image->win_ptr, data->base_image->img_ptr, 0, 0);
}

void	*sphere_transform(void *content)
{
	t_sphere	*sphere;

	sphere = content;
	sphere->radius = sphere->diameter / 2;
	sphere->transform = translation(
			sphere->center.x, sphere->center.y, sphere->center.z);
	return (sphere);
}

void	init_world(t_data *data)
{
	data->scene->world.ambient = data->scene->ambient;
	data->scene->world.light = point_light(
			data->scene->light.position,
			data->scene->light.intensity,
			data->scene->light.color);
	configure_camera(&data->scene->camera);
	data->scene->world.objects = ft_lstmap(
			data->scene->spheres, sphere_transform, free);
}
