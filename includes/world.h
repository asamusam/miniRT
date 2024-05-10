/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:07:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/09 17:50:55 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "light.h"
# include "shapes.h"

typedef struct s_data			t_data;
typedef struct s_cam			t_cam;
typedef struct s_light			t_light;
typedef struct s_ambient		t_ambient;
typedef struct s_tuple			t_tuple;
typedef struct s_ray			t_ray;
typedef struct s_color			t_color;
typedef struct s_matrix			t_matrix;
typedef struct s_intersection	t_intersection;

typedef struct s_world
{
	t_list		*objects;
	t_light		light;
	t_ambient	ambient;
}	t_world;

typedef struct s_comps
{
	float		t;
	t_sphere	sphere;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	t_tuple		over_point;
	bool		inside;
}	t_comps;

typedef struct s_camconfig
{
	t_tuple		forward;
	t_tuple		upn;
	t_tuple		left;
	t_tuple		true_up;
}	t_camconfig;

typedef struct s_world_coord
{
	float	world_x;
	float	world_y;
}	t_world_coord;

t_world		default_world(void);
void		init_world(t_data *data);
t_list		*intersect_world(t_world world, t_ray ray);
t_comps		prepare_computations(t_intersection intersection, t_ray ray);
t_color		shade_hit(t_world world, t_comps comps);
t_color		color_at(t_world world, t_ray ray);
t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up);
t_cam		camera(float hsize, float vsize, float field_of_view);
void		configure_camera(t_data *data, t_cam *c);
t_ray		ray_for_pixel(t_cam camera, float px, float py);
void		render(t_data *data, t_cam camera, t_world world);

#endif // !WORLD_H
