/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 15:14:34 by llai             ###   ########.fr       */
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

int	main(void)
{
	t_data	data;
	t_win	win;

	data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
	win = data.base_image.win;
	data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);

	// test1();
	// test2();
	test3();
	// put_pixel(data.base_image, 0, 0, color(0, 1, 0, 0));
	// mlx_put_image_to_window(data.base_image.win.mlx,
	// 	data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);

	mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
	mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
	mlx_loop(data. base_image.win.mlx);
}
