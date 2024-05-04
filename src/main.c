/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/04 16:15:04 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <stdlib.h>

void	draw_scene(t_data *data);

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
		put_pixel_img(data->base_image, 0, 0, create_trgb(0, 1, 0, 0));
		// printf("here\n");
		// render(data, data->scene->camera, data->scene->world);
		mlx_put_image_to_window(data->base_image->mlx, \
								data->base_image->win_ptr, \
								data->base_image->img_ptr, 0, 0);
		mlx_hook(data->base_image->win_ptr, 2, 1L << 0, esc_close_win, data);
		mlx_hook(data->base_image->win_ptr, 17, 0, cross_close_win, data);
		mlx_loop(data->base_image->mlx);
	}
}
