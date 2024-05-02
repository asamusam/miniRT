/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 17:29:18 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_win	new_window(int w, int h, char *str)
{
	void	*mlx;

	mlx = mlx_init();
	return ((t_win){mlx, mlx_new_window(mlx, w, h, str), w, h});
}

void	init_data(t_data *data)
{
	data->scene.ambient.color = color(0, 0, 0, 0);
	data->scene.ambient.intensity = 0.0;
	data->scene.camera.distance = 0.0;
	data->scene.camera.fov = 0;
	data->scene.camera.position = (t_tuple){0, 0, 0, POINT};
	data->scene.camera.rotation = (t_tuple){0, 0, 0, VECTOR};
	data->scene.light.color = color(0, 0, 0, 0);
	data->scene.light.intensity = 0.0;
	data->scene.light.position = (t_tuple){0, 0, 0, POINT};
	data->scene.cylinders = NULL;
	data->scene.planes = NULL;
	data->scene.spheres = NULL;
}
