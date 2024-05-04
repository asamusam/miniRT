/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/04 17:37:53 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <stdlib.h>

void	draw_scene(t_data *data);

void	sphere_scene(t_data *data)
{
	t_cam	c = camera(HEIGHT, WIDTH, M_PI / 2);
	t_tuple	from = point(0, 0, -5);
	t_tuple	to = point(0, 0, 0);
	t_tuple	up = vector(0, 1, 0);
	// data->scene->camera.transform = view_transform(from, to, up);
	c.transform = view_transform(from, to, up);
	t_world	w;

	w = world();
	w.light = point_light(point(-10, 10, -10), color(0, 1, 1, 1));
	t_sphere	s = sphere(point(0, 0, 0), 1);
	s.material = material();
	s.material.color = color(0, 1, 0.2, 1);
	ft_lstadd_back(&w.objects, ft_lstnew(&s));
	// render(data, data->scene->camera, data->scene->world);
	render(data, c, w);
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
		print_scene(data);
		init_mlx(data);
		// put_pixel_img(data->base_image, 0, 0, create_trgb(0, 1, 0, 0));
		printf("render\n");
		// render(data, data->scene->camera, data->scene->world);
		sphere_scene(data);
		mlx_loop(data->base_image->mlx);
	}
}
