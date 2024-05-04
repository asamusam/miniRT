/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:23:30 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/04 15:46:17 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "shapes.h"
# include "light.h"
# include "world.h"

typedef struct s_cam
{
	t_tuple		position;
	t_tuple		rotation;
	// float		distance;
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
