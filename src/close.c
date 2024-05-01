/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:03 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 19:46:59 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_data *data)
{
	if (data->scene.spheres)
		ft_lstclear(&data->scene.spheres, free);
	if (data->scene.cylinders)
		ft_lstclear(&data->scene.cylinders, free);
	if (data->scene.planes)
		ft_lstclear(&data->scene.planes, free);
}

int	destroy_window(t_data *data)
{
	mlx_destroy_window(data->base_image.win.mlx, data->base_image.win.win_ptr);
	free(data->base_image.win.mlx);
	free_scene(data);
	exit(EXIT_SUCCESS);
}

int	esc_close_win(int keycode, t_data *data)
{
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
