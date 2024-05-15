/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:05:37 by llai              #+#    #+#             */
/*   Updated: 2024/05/15 13:18:06 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/world.h"
#include "../includes/ray.h"
#include "../includes/matrix.h"
#include "../includes/debug.h"
#include "../includes/world.h"
#include "../includes/scene.h"
#include "../includes/image.h"
#include <stdbool.h>
#include <stdio.h>

static float	calc_offset(t_cam *camera, float p)
{
	return ((p + 0.5) * camera->pixel_size);
}

// It returns new ray from the camera and passes through 
// the indicated (x, y) pixel on the canvas
void	ray_for_pixel(t_cam *camera, float px, float py, t_ray *r)
{
	t_world_coord	wc;
	t_tuple			pixel;
	t_tuple			origin;
	t_tuple			direction;
	t_matrix		inv_m;

	inverse(&camera->transform, &inv_m);
	wc.world_x = camera->half_width - calc_offset(camera, px);
	wc.world_y = camera->half_height - calc_offset(camera, py);
	matrix_tuple_multiply(&inv_m, point(wc.world_x, wc.world_y, -1), &pixel);
	matrix_tuple_multiply(&inv_m, point(0, 0, 0), &origin);
	direction = normalize(sub_tuples(pixel, origin));
	r->origin = origin;
	r->direction = direction;
}

void	color_at(t_world *world, t_ray *ray, t_color *c)
{
	t_list				*intersections;
	t_shape_intersect	*i;
	t_shape_comps		comps;
	bool				shadowed;

	intersections = intersect_world(world, ray);
	i = hit(intersections);
	if (i == NULL)
	{
		ft_lstclear(&intersections, free);
		*c = color(0, 0, 0, 0);
		return ;
	}
	prepare_comps(i, ray, &comps);
	shadowed = is_shadowed(world, comps.over_point);
	*c = lighting(world, &comps, shadowed);
	ft_lstclear(&intersections, free);
}

void	render(t_data *data)
{
	t_ray			r;
	t_color			color;
	int				x;
	int				y;
	t_progresbar	pb;

	pb.total_pixels = data->scene->camera.vsize * data->scene->camera.hsize;
	pb.current_pixel = 0;
	y = -1;
	while (++y < data->scene->camera.vsize)
	{
		x = -1;
		while (++x < data->scene->camera.hsize)
		{
			ray_for_pixel(&data->scene->camera, x, y, &r);
			color_at(&data->scene->world, &r, &color);
			put_pixel2(data->base_image, x, y, color);
			pb.current_pixel++;
			pb.progress = (float)pb.current_pixel / pb.total_pixels;
			print_progress(pb.progress);
		}
	}
	mlx_put_image_to_window(data->base_image->mlx,
		data->base_image->win_ptr, data->base_image->img_ptr, 0, 0);
}
