/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 16:53:13 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <math.h>

void	test1(void)
{
	t_sphere	s = sphere(point(0, 0, 0), 1);

	t_tuple	n = normal_at(s, point(0, 0, 1));
	print_tuple(n);
}

void	test2(void)
{
	t_sphere	s = sphere(point(0, 0, 0), 1);
	t_matrix	m = matrix_multiply(scaling(1, 0.5, 1), rotation_z(M_PI / 5));

	set_transform(&s, m);
	t_tuple	n = normal_at(s, point(0, sqrt(2) / 2, -sqrt(2) / 2));
	print_tuple(n);
}

void	test3(void)
{
	t_tuple	in = vector(0, -1, 0);
	t_tuple	n = vector(sqrt(2) / 2, sqrt(2) / 2, 0);

	t_tuple	r = reflect(in, n);
	print_tuple(r);
}

void	test4(void)
{
	t_sphere	s = sphere(point(0, 0, 0), 1);
	t_material	m = material();

	m.ambient = 1;
	s.material = m;
	printf("m: %f\n", s.material.ambient);
}

void	test5(void)
{
	t_material	m = material();
	t_tuple		p = point(0, 0, 0);
	t_tuple	eyev = vector(0, 0, -1);
	t_tuple	normalv = vector(0, 0, -1);
	t_light	light = point_light(point(0, 10, -10), color(0, 1, 1, 1));

	t_color	res = lighting(m, light, p, eyev, normalv);
	printf("r: %f, g: %f, b:%f\n", res.red, res.green, res.blue);
}

void	draw_sphere(t_data *data)
{
	(void)data;
	t_tuple	ray_origin = point(0, 0, -5);
	double	wall_z = 10;
	double	wall_size = 7;
	double	canvas_pixel = 100;
	double	pixel_size = wall_size / canvas_pixel;
	// double	half = wall_size / 2;

	t_sphere	s = sphere(point(0, 0, 0), 1);
	s.material = material();
	s.material.color = color(0, 1, 0.2, 1);

	t_tuple	light_pos = point(-10, 10, -10);
	t_color	light_color = color(0, 1, 1, 1);
	t_light	light = point_light(light_pos, light_color);

	for (int y = -canvas_pixel / 2; y < canvas_pixel / 2; y++)
	{
		double	world_y = pixel_size * y;
		for (int x = -canvas_pixel / 2; x < canvas_pixel / 2; x++)
		{
			double	world_x = pixel_size * x;
			t_tuple	pos = point(world_x, world_y, wall_z);
			// t_tuple	position = point(x, y, wall_z);
			t_ray	r = ray(ray_origin, normalize(sub_tuples(pos, ray_origin)));
			t_list *xs = NULL;
			// s.transform = scaling(1, 0.5, 1);
			// s.transform = scaling(0.5, 1, 1);
			// s.transform = matrix_multiply(rotation_z(M_PI / 4) ,scaling(0.5, 1, 1));
			// s.transform = matrix_multiply(shearing(1, 0, 0, 0, 0, 0), scaling(0.5, 1, 1));
			xs = intersect(s, r);
			t_intersection	*i = hit(xs);
			if (i && i->t)
			{
				// printf("res: %f\n", i->t);
				t_tuple point = position(r, i->t);
				t_tuple	normal = normal_at(i->object, point);
				t_tuple	eyev = negate_tuple(r.direction);
				t_color color = lighting( i->object.material, light, point, eyev, normal);
				// put_pixel(data->base_image, x, y, color(0, 1, 0, 0));
				put_pixel(data->base_image, x, y, color);
			}
			else
			{
				put_pixel(data->base_image, x, y, color(0, 0, 0, 0));
			}
		}
	}
}

int	main(void)
{
	t_data	data;
	t_win	win;

	data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
	win = data.base_image.win;
	data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);

	// test1();
	// test2();
	// test3();
	// test4();
	// test5();
	draw_sphere(&data);
	// put_pixel(data.base_image, 0, 0, color(0, 1, 1, 1));
	mlx_put_image_to_window(data.base_image.win.mlx,
		data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);

	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}
