/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:23:30 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/13 16:33:52 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "tuples.h"
# include "light.h"
# include "world.h"

typedef struct s_matrix		t_matrix;
typedef struct s_light		t_light;
typedef struct s_list		t_list;
typedef struct s_ambient	t_ambient;

typedef struct s_cam
{
	t_tuple		position;
	t_tuple		rotation;
	float		fov;
	float		hsize;
	float		vsize;
	float		rfov;
	float		half_width;
	float		half_height;
	float		pixel_size;
	t_matrix	transform;
}	t_cam;

typedef struct s_scene
{
	t_cam		camera;
	t_light		light;
	t_ambient	ambient;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	t_world		world;
}	t_scene;

#endif
