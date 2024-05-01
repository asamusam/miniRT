/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 20:09:49 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_win	win;

	if (ac == 2)
	{
		init_data(&data);
		if (parse(&data, av[1]) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		data.base_image.win = new_window(WIDTH, HEIGHT, "miniRT");
		win = data.base_image.win;
		data.base_image = new_img(WIDTH, HEIGHT, data.base_image.win);
		put_pixel(data.base_image, 0, 0, create_trgb(0, 1, 0, 0));
		mlx_put_image_to_window(data.base_image.win.mlx,
			data.base_image.win.win_ptr, data.base_image.img_ptr, 0, 0);
		mlx_hook(win.win_ptr, 2, 1L << 0, esc_close_win, &data);
		mlx_hook(win.win_ptr, 17, 0, cross_close_win, &data);
		mlx_loop(data. base_image.win.mlx);
	}
}
