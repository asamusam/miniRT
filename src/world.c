/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 20:41:08 by llai             ###   ########.fr       */
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
		ft_lstadd_back(&result, intersect((t_sphere *)tmp->content, ray));
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
	{
		ft_lstclear(&intersections, free);
		return (color(0, 0, 0, 0));
	}
	ft_lstclear(&intersections, free);
	comps = prepare_computations(*i, ray);
	c = shade_hit(world, comps);
	return (c);
}

t_matrix	*make_orientation(t_tuple left, t_tuple true_up, t_tuple forward)
{
	t_matrix	*orientation;

	orientation = create_matrix(4, 4);
	orientation->data[0][0] = left.x;
	orientation->data[0][1] = left.y;
	orientation->data[0][2] = left.z;
	orientation->data[0][3] = 0;
	orientation->data[1][0] = true_up.x;
	orientation->data[1][1] = true_up.y;
	orientation->data[1][2] = true_up.z;
	orientation->data[1][3] = 0;
	orientation->data[2][0] = -forward.x;
	orientation->data[2][1] = -forward.y;
	orientation->data[2][2] = -forward.z;
	orientation->data[2][3] = 0;
	orientation->data[3][0] = 0;
	orientation->data[3][1] = 0;
	orientation->data[3][2] = 0;
	orientation->data[3][3] = 1;
	return (orientation);
}

// It mimics the eye/camera moves instead of the world
// from where the eye in the scene
// to where you want to look at
// and a vector indicates which direction is up
t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		upn;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	*orientation;
	t_matrix	*trans_m;
	t_matrix	*res;

	forward = normalize(to);
	if (equal_tuple(forward, vector(0, 1, 0)) || equal_tuple(forward, vector(0, -1, 0)))
	{
		perror("Invalid orientation vector:gimbal lock");
		exit(EXIT_FAILURE);
	}
	upn = normalize(up);
	left = cross(forward, upn);
	true_up = cross(left, forward);
	orientation = make_orientation(left, true_up, forward);
	trans_m = translation(-from.x, -from.y, -from.z);
	res = matrix_multiply(*orientation, *trans_m);
	free_matrix(&trans_m);
	free_matrix(&orientation);
	return (res);

	// return (matrix_multiply(*orientation,
	// 		translation(-from.x, -from.y, -from.z)));
}

t_cam	camera(float hsize, float vsize, float field_of_view)
{
	t_cam		c;
	float		half_view;
	float		aspect;
	t_matrix	*m;

	c.hsize = hsize;
	c.vsize = vsize;
	c.rfov = field_of_view;
	m = init_identitymatrix(4);
	// c.transform = init_identitymatrix(4);
	c.transform = m;
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
void	configure_camera(t_data *data, t_cam *c)
{
	float		half_view;
	float		aspect;
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	// t_matrix	*m;

	c->hsize = WIDTH;
	c->vsize = HEIGHT;
	c->rfov = radians(c->fov);
	from = data->scene->camera.position;
	to = data->scene->camera.rotation;
	up = vector(0, 1, 0);
	data->scene->camera.transform = view_transform(from, to, up);
	// c->transform = init_identitymatrix(4);
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
	t_matrix	*inv_m;

	inv_m = inverse(*camera.transform);
	world_x = camera.half_width - calc_offset(camera, px);
	world_y = camera.half_height - calc_offset(camera, py);
	pixel = matrix_tuple_multiply(
			*inv_m, point(world_x, world_y, -1));
	origin = matrix_tuple_multiply(
			*inv_m, point(0, 0, 0));
	free_matrix(&inv_m);
	direction = normalize(sub_tuples(pixel, origin));
	return (ray(origin, direction));
}

void	print_progress(float progress)
{
	int	bar_len;
	int	completed_len;
	int	i;

	bar_len = 20;
	completed_len = progress * bar_len;
	printf("\r[");
	i = -1;
	while (++i < completed_len)
		printf("#");
	i = completed_len;
	while (i++ < bar_len)
		printf(" ");
	printf("] %.2f%%", progress * 100);
	fflush(stdout);
}

void	render(t_data *data, t_cam camera, t_world world)
{
	t_ray	r;
	t_color	color;
	int		x;
	int		y;
	int		total_pixels = camera.vsize * camera.hsize;
	int		current_pixel = 0;

	y = -1;
	while (++y < camera.vsize)
	{
		x = -1;
		while (++x < camera.hsize)
		{
			r = ray_for_pixel(camera, x, y);
			color = color_at(world, r);
			put_pixel2(data->base_image, x, y, color);
			current_pixel++;
			float	progress = (float)current_pixel / total_pixels;
			print_progress(progress);
		}
	}
	mlx_put_image_to_window(data->base_image->mlx,
		data->base_image->win_ptr, data->base_image->img_ptr, 0, 0);
}

void	*sphere_transform(void *content)
{
	t_sphere	*sphere;
	// t_matrix	*trans_m;

	sphere = content;
	sphere->radius = sphere->diameter / 2;
	// trans_m = translation(sphere->center.x, sphere->center.y, sphere->center.z);
	sphere->transform = translation(sphere->center.x, sphere->center.y, sphere->center.z);
	// sphere->transform = translation(
	// 		sphere->center.x, sphere->center.y, sphere->center.z);
	return (sphere);
}

void	init_world(t_data *data)
{
	data->scene->world.ambient = data->scene->ambient;
	data->scene->world.light = data->scene->light;
	configure_camera(data, &data->scene->camera);
	data->scene->world.objects = ft_lstmap(
			data->scene->spheres, sphere_transform, free);
}
