/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/05 02:27:01 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"

void	draw_scene(t_data *data);

t_tuple	camera_up(t_tuple default_up, t_tuple rotation)
{
	t_tuple	right;
	t_tuple	n_right;
	t_tuple	update_up;

	right = cross(default_up, rotation);
	n_right = normalize(right);
	update_up = cross(rotation, n_right);
	return (update_up);
}

void	sphere_scene(t_data *data)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = data->scene->camera.position;
	// from = point(0, 0, -5);
	to = point(0, 0, 0);
	up = vector(0, 1, 0);
	data->scene->camera.transform = view_transform(from, to, up);
	render(data, data->scene->camera, data->scene->world);
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
		printf("render\n");
		sphere_scene(data);
		mlx_loop(data->base_image->mlx);
	}
}
