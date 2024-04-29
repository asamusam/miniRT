/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:03 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:43:04 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	destroy_window(t_data *data)
{
	// free_images(data);
	// free_gamemap(data);
	mlx_destroy_window(data->base_image.win.mlx, data->base_image.win.win_ptr);
	free(data->base_image.win.mlx);
	exit(EXIT_SUCCESS);
}

int	esc_close_win(int keycode, t_data *data)
{
	// printf("Key: %d\n", keycode);
	if (keycode == ESC_KEY)
	{
		destroy_window(data);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	cross_close_win(t_data *data)
{
	destroy_window(data);
	exit(EXIT_SUCCESS);
}
