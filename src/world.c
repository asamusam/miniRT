/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:10:46 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 12:56:31 by llai             ###   ########.fr       */
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
	t_world	new_world = world();

	// new_world.spheres
	// ft_lstadd_back(&new_world.spheres, ft_lstnew(sphere(point(0, 0, 0), 0.5)));
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

void	insertion_sortlist(t_list **head)
{
	t_list *sorted = NULL;
    t_list *current = *head;

    while (current != NULL)
    {
        t_list *next = current->next;

        // Find the correct position to insert current in the sorted list
        if (sorted == NULL || *(double *)sorted->content >= *(double *)current->content)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            t_list *temp = sorted;
            while (temp->next != NULL && *(double *)temp->next->content < *(double *)current->content)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    // Update head_ref to point to the sorted list
    *head = sorted;
}

t_list *intersect_world(t_world world, t_ray ray)
{
	t_list	*result = NULL;
	int	i = -1;

	while (++i < world.obj_nb)
	{
		ft_lstadd_back(&result,	intersect(world.spheres[i], ray));
	}
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
	return (lighting(comps.sphere.material, world.light, comps.point, comps.eyev, comps.normalv));
}

t_color	color_at(t_world world, t_ray ray)
{
	t_list *intersections;
	intersections = intersect_world(world, ray);
	t_intersection	*i = hit(intersections);
	if (i == NULL)
		return (color(0, 0, 0, 0));
	t_comps comps = prepare_computations(*i, ray);
	t_color	color = shade_hit(world, comps);
	return (color);
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forword = normalize(sub_tuples(to, from));
	t_tuple	upn = normalize(up);
	t_tuple	left = cross(forword, upn);
	t_tuple	true_up = cross(left, forword);
	t_matrix	orientation = create_matrix(4, 4);
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
	return (matrix_multiply(orientation, translation(-from.x, -from.y, -from.z)));
}

t_camera	camera(double hsize, double vsize, double field_of_view)
{
	t_camera	c;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	c.transform = init_identitymatrix(4);

	double	half_view = tan(c.field_of_view / 2);
	double	aspect = c.hsize / c.vsize;

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

t_ray	ray_for_pixel(t_camera camera, double px, double py)
{
	double	xoffset = (px + 0.5) * camera.pixel_size;
	double	yoffset = (py + 0.5) * camera.pixel_size;

	double	world_x = camera.half_width - xoffset;
	double	world_y = camera.half_height - yoffset;

	t_tuple	pixel = matrix_tuple_multiply(inverse(camera.transform), point(world_x, world_y, -1));
	t_tuple	origin = matrix_tuple_multiply(inverse(camera.transform), point(0, 0, 0));
	t_tuple	direction = normalize(sub_tuples(pixel, origin));

	return (ray(origin, direction));
}

void	render(t_data *data, t_camera camera, t_world world)
{
	// (void)world;
	data->base_image.win = new_window(camera.hsize, camera.vsize, "miniRT");
	data->base_image = new_img(camera.hsize, camera.vsize, data->base_image.win);

	// for (int y = -camera.vsize / 2; y < camera.vsize / 2; y++)
	for (int y = 0; y < camera.vsize; y++)
	{
		// for (int x = -camera.hsize / 2; x < camera.hsize / 2; x++)
		for (int x = 0; x < camera.hsize; x++)
		{
			t_ray	r = ray_for_pixel(camera, x, y);
			t_color	color = color_at(world, r);
			// put_pixel(data->base_image, x, y, color);
			put_pixel2(data->base_image, x, y, color);
			// printf("x: %d y: %d\n", x, y);
		}
	}

	mlx_put_image_to_window(data->base_image.win.mlx,
		data->base_image.win.win_ptr, data->base_image.img_ptr, 0, 0);
	// data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
	// win = data.base_image.win;
	// data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);


	// put_pixel(data.base_image, 0, 0, color(0, 1, 1, 1));
}
