/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 13:38:19 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <math.h>
#include <stdio.h>

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

t_tuple	calc_rotation_angles(t_tuple original, t_tuple new)
{
	t_tuple	res;

	res.x = atan2(new.y, new.z) - atan2(original.y, original.z);
	res.y = atan2(new.x, new.z) - atan2(original.x, original.z);
	res.z = atan2(new.y, new.x) - atan2(original.y, original.x);
	res.w = -1;
	return (res);
}

void	camera_rotation(t_cam *camera)
{
	t_tuple	original;
	t_tuple	rad;
	t_matrix	m;

	original = vector(0, 0, 1);
	printf("rotation:");
	print_tuple2(camera->rotation);
	rad = calc_rotation_angles(original, camera->rotation);
	m = matrix_multiply(rotation_z(rad.z), matrix_multiply(rotation_x(rad.x), rotation_y(rad.y)));
	camera->transform = matrix_multiply(camera->transform, m);
}

void	rotate_x(t_tuple *point, float angle)
{
	float	y = point->y * cos(angle) - point->z * sin(angle);
	float	z = point->y * sin(angle) + point->z * cos(angle);
	point->y = y;
	point->z = z;
}

void	sphere_scene(t_data *data)
{
	t_tuple	from;
	t_tuple	to;
	t_tuple	up;

	from = data->scene->camera.position;
	to = data->scene->camera.rotation;
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
