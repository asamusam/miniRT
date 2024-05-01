/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:23:30 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/01 17:17:35 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "shapes.h"
# include "light.h"

typedef struct s_cam
{
	t_tuple		position;
	t_tuple		rotation;
	float		distance;
	float		fov;
}	t_cam;

typedef struct s_scene
{
	t_cam		camera;
	t_light		light;
	t_ambient	ambient;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

#endif