/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 17:15:10 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../libft/libft.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

t_world	world(void)
{
	t_world	world;

	world.spheres = NULL;
	world.light = point_light(point(0, 0, 0), color(0, 1, 1, 1));
	return (world);
}

t_world	default_world(void)
{
	t_world	new_world;

	new_world = world();
	new_world.obj_nb = 2;
	new_world.spheres = malloc(2 * sizeof(t_sphere));
	new_world.spheres[0] = sphere(point(0, 0, 0), 1);
	new_world.spheres[0].material.color = color(0, 0.8, 1, 0.6);
	new_world.spheres[0].material.diffuse = 0.7;
	new_world.spheres[0].material.specular = 0.2;
	new_world.spheres[1] = sphere(point(0, 0, 0), 1);
	new_world.spheres[1].transform = scaling(0.5, 0.5, 0.5);
	new_world.light = point_light(point(-10, 10, -10), color(0, 1, 1, 1));
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
	int		i;

	result = NULL;
	i = -1;
	while (++i < world.obj_nb)
		ft_lstadd_back(&result, intersect(world.spheres[i], ray));
	insertion_sortlist(&result);
	return (result);
}

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

t_camera	camera(float hsize, float vsize, float field_of_view)
{
	t_camera	c;
	float		half_view;
	float		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	c.transform = init_identitymatrix(4);
	half_view = tan(c.field_of_view / 2);
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

float	calc_offset(t_camera camera, float p)
{
	return ((p + 0.5) * camera.pixel_size);
}

t_ray	ray_for_pixel(t_camera camera, float px, float py)
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

void	render(t_data *data, t_camera camera, t_world world)
{
	t_ray	r;
	t_color	color;
	int		x;
	int		y;

	data->base_image.win = new_window(camera.hsize, camera.vsize, "miniRT");
	data->base_image = new_img(
			camera.hsize, camera.vsize, data->base_image.win);
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
	mlx_put_image_to_window(data->base_image.win.mlx,
		data->base_image.win.win_ptr, data->base_image.img_ptr, 0, 0);
}
