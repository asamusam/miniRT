/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:07:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 15:00:58 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include "matrix.h"
#include "shapes.h"
#include "tuples.h"

typedef struct s_data t_data;

typedef struct s_world
{
	int			obj_nb;
	t_sphere	*spheres;
	// t_list		*spheres;
	t_light		light;
}	t_world;

typedef struct s_comps
{
	double	t;
	t_sphere	sphere;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	bool		inside;
}	t_comps;

typedef struct s_camera
{
	double	hsize;
	double	vsize;
	double	field_of_view;
	double	half_width;
	double	half_height;
	double	pixel_size;
	t_matrix	transform;
}	t_camera;

t_world	world(void);
t_world	default_world(void);
t_list *intersect_world(t_world world, t_ray ray);
t_comps	prepare_computations(t_intersection intersection, t_ray ray);
t_color	shade_hit(t_world world, t_comps comps);
t_color	color_at(t_world world, t_ray ray);
t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up);
t_camera	camera(double hsize, double vsize, double field_of_view);
t_ray	ray_for_pixel(t_camera camera, double px, double py);
void	render(t_data *data, t_camera camera, t_world world);

#endif // !WORLD_H
