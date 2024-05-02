/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 20:21:00 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include <stdlib.h>

void	draw_scene(t_data *data);

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
}
