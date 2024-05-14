/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:07:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/14 19:54:22 by llai             ###   ########.fr       */
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

typedef struct s_shape_comps
{
	float		t;
	t_object	*object;
	t_tuple		point;
	t_tuple		eyev;
	t_tuple		normalv;
	t_tuple		over_point;
	bool		inside;
}	t_shape_comps;

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

void			init_world(t_data *data);
t_list			*intersect_world(t_world *world, t_ray *ray);
void			prepare_comps(t_shape_intersect *intersect,
					t_ray *ray, t_shape_comps *comps);
void			color_at(t_world *world, t_ray *ray, t_color *c);
void			view_transform(t_tuple from, t_tuple to,
					t_tuple up, t_matrix *res);
void			configure_camera(t_data *data, t_cam *c);
void			ray_for_pixel(t_cam *camera, float px, float py, t_ray *r);
void			render(t_data *data);

#endif // !WORLD_H
