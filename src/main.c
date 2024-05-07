/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 18:51:37 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>

void	draw_scene(t_data *data);

void	sphere_scene(t_data *data)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;
	// t_matrix	*cam_m;

	from = data->scene->camera.position;
	to = data->scene->camera.rotation;
	up = vector(0, 1, 0);
	// cam_m = view_transform(from, to, up);
	// data->scene->camera.transform = view_transform(from, to, up);
	data->scene->camera.transform = view_transform(from, to, up);
	render(data, data->scene->camera, data->scene->world);
	// free_matrix(cam_m);
	printf("done\n");
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		allocate_data(&data);
		init_data(data);
		parse(data, av[1]);
		init_world(data);
		// print_scene(data);
		init_mlx(data);
		printf("render\n");
		init_objects(data);
		sphere_scene(data);
		mlx_loop(data->base_image->mlx);
	}
}
