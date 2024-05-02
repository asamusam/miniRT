/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 16:35:42 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
	printf("t: %f, r: %f, g: %f, b:%f\n", res.transparent, res.red, res.green, res.blue);
}

void	draw_sphere(t_data *data)
{
	(void)data;
	t_tuple	ray_origin = point(0, 0, -5);
	double	wall_z = 10;
	double	wall_size = 7;
	double	canvas_pixel = 1080;
	double	pixel_size = wall_size / canvas_pixel;
	// double	half = wall_size / 2;

	// t_sphere	s = sphere(point(0, 0, 0), 1);
	// s.material = material();
	// s.material.color = color(0, 1, 0.2, 1);

	t_sphere s = sphere(point(0, 0, 0), 1);
	s.material.color = color(0, 0.8, 1, 0.6);
	s.material.diffuse = 0.7;
	s.material.specular = 0.2;

	// t_sphere s = sphere(point(0, 0, 0), 1);
	// s.transform = scaling(0.5, 0.5, 0.5);

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
			s.transform = matrix_multiply(rotation_z(M_PI / 4) ,scaling(0.5, 1, 1));
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

void	test6(void)
{
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_list	*xs = intersect_world(w, r);
	if (xs)
	{
		printf("count: %d\n", ft_lstsize(xs));
		while (xs)
		{
			t_intersection	*i = xs->content;
			printf("t: %f\n", i->t);
			xs = xs->next;
		}
	}
}

void	test7(void)
{
	t_ray	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_sphere	s = sphere(point(0, 0, 0), 1);
	t_intersection	*i = intersection(1, s);
	t_comps	comps = prepare_computations(*i, r);

	printf("t: %f\n", comps.t);
	printf("radius: %f\n", comps.sphere.radius);
	print_tuple(comps.sphere.center);
	print_tuple(comps.point);
	print_tuple(comps.eyev);
	print_tuple(comps.normalv);
	printf("inside: %d\n", comps.inside);
}

void	test8(void)
{
	t_world	w = default_world();
	w.light = point_light(point(0, 0.25, 0), color(0, 1, 1, 1));
	t_ray	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_sphere s = w.spheres[1];
	t_intersection *i = intersection(0.5, s);
	t_comps comps = prepare_computations(*i, r);
	t_color c = shade_hit(w, comps);

	print_color(c);
}

void	test9(void)
{
	t_world	w = default_world();
	t_sphere *outer = &w.spheres[0];
	outer->material.ambient = 1;
	t_sphere *inner = &w.spheres[1];
	inner->material.ambient = 1;
	t_ray	r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	t_color	c = color_at(w, r);
	print_color(c);
	print_color(inner->material.color);
}

void	test10(void)
{
	t_tuple	from = point(1, 3, 2);
	t_tuple	to = point(4, -2, 8);
	t_tuple	up = vector(1, 1, 0);
	t_matrix	t = view_transform(from, to, up);
	print_matrix(t);
}

void	test10b(void)
{
	t_tuple	from = point(0, 0, 8);
	t_tuple	to = point(0, 0, 0);
	t_tuple	up = vector(0, 1, 0);
	t_matrix	t = view_transform(from, to, up);
	print_matrix(t);
	t = translation(0, 0, -8);
	print_matrix(t);
}

void	test11(void)
{
	t_camera	c = camera(200, 125, M_PI / 2);
	printf("%f\n", c.pixel_size);
	c = camera(125, 200, M_PI / 2);
	printf("%f\n", c.pixel_size);
}

void	test12(void)
{
	t_camera	c = camera(201, 101, M_PI / 2);
	t_ray	r = ray_for_pixel(c, 0, 0);
	print_tuple(r.origin);
	print_tuple(r.direction);
}

void	test13(t_data *data)
{
	t_world	w = default_world();
	t_camera c = camera(1100, 1100, M_PI / 2);
	t_tuple	from = point(0, 0, -5);
	t_tuple	to = point(0, 0, 0);
	t_tuple	up = vector(0, 1, 0);
	c.transform = view_transform(from, to, up);

	render(data, c, w);
}

void	draw_scene(t_data *data)
{
	t_sphere	floor = sphere(point(0, 0, 0), 1);
	floor.transform = scaling(10, 0.01, 10);
	floor.material = material();
	floor.material.color = color(0, 1, 0.9, 0.9);
	floor.material.specular = 0;

	t_sphere	left_wall = sphere(point(0, 0, 0), 1);
	left_wall.transform = matrix_multiply(matrix_multiply(matrix_multiply(translation(0, 0, 5), rotation_y(-(M_PI / 4))), rotation_x(M_PI / 2)), scaling(10, 0.01, 10));
	// left_wall.transform = matrix_multiply(translation(0, 0, 5), rotation_y(-M_PI / 4));
	// left_wall.transform = matrix_multiply(left_wall.transform, rotation_x(M_PI / 2));
	// left_wall.transform = matrix_multiply(left_wall.transform, scaling(10, 0.01, 10));
	left_wall.material = floor.material;

	t_sphere	right_wall = sphere(point(0, 0, 0), 1);
	right_wall.transform = matrix_multiply(matrix_multiply(matrix_multiply(translation(0, 0, 5), rotation_y(M_PI / 4)), rotation_x(M_PI / 2)), scaling(10, 0.01, 10));
	// left_wall.transform = matrix_multiply(translation(0, 0, 5), rotation_y(M_PI / 4));
	// left_wall.transform = matrix_multiply(left_wall.transform, rotation_x(M_PI / 2));
	// left_wall.transform = matrix_multiply(left_wall.transform, scaling(10, 0.01, 10));
	right_wall.material = floor.material;

	t_sphere	middle = sphere(point(0, 0, 0), 1);
	middle.transform = translation(-0.5, 1, 0.5);
	middle.material = material();
	middle.material.color = color(0, 0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	t_sphere	right = sphere(point(0, 0, 0), 1);
	right.transform = matrix_multiply(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5));
	right.material = material();
	right.material.color = color(0, 0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	t_sphere	left = sphere(point(0, 0, 0), 1);
	left.transform = matrix_multiply(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33));
	left.material = material();
	left.material.color = color(0, 1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	t_world	w = world();
	w.light = point_light(point(-10, 10, -10), color(0, 1, 1, 1));
	w.obj_nb = 6;
	w.spheres = malloc(sizeof(t_sphere) * w.obj_nb);
	w.spheres[0] = floor;
	w.spheres[1] = middle;
	w.spheres[2] = right;
	w.spheres[3] = left;
	w.spheres[4] = left_wall;
	w.spheres[5] = right_wall;
	// (void)right_wall;
	// (void)left_wall;
	// (void)floor;
	// (void)right;
	// (void)left;
	// (void)middle;
	t_camera c = camera(100 * 6, 50 * 6, M_PI / 3);
	t_tuple	from = point(0, 1.5, -5);
	t_tuple	to = point(0, 1, 0);
	t_tuple	up = vector(0, 1, 0);
	c.transform = view_transform(from, to, up);
	// c.transform = view_transform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0));
	render(data, c, w);
	printf("done\n");
}

void	test14(void)
{
	t_tuple v1 = vector(4, 0, 0);
	t_tuple v2 = vector(-4, 3, 9);
	// printf("%f\n", magnitude(v));
	// printf("%f\n", magnitude(normalize(v)));
	// print_tuple(normalize(v));
	printf("%f %f\n", dot(v1, v2), dot(normalize(v1), normalize(v2)));
}

int	main(int ac, char **av)
{
	t_data	data;
	t_win	win;

	if (ac == 2)
	{
		init_data(&data);
		if (parse(&data, av[1]) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		draw_scene(&data);
		win = data.base_image.win;
		mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
		mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
		mlx_loop(data. base_image.win.mlx);
	}
	test14();
}
