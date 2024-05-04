/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:03 by llai              #+#    #+#             */
/*   Updated: 2024/05/04 13:55:25 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	free_data(t_data *data)
{
	if (data->base_image)
		free(data->base_image);
	if (data->scene)
	{
		if (data->scene->spheres)
			ft_lstclear(&data->scene->spheres, free);
		if (data->scene->cylinders)
			ft_lstclear(&data->scene->cylinders, free);
		if (data->scene->planes)
			ft_lstclear(&data->scene->planes, free);
		free(data->scene);
	}
	free(data);
}

int	destroy_window(t_data *data)
{
	mlx_destroy_image(data->base_image->mlx, data->base_image->img_ptr);
	mlx_destroy_window(data->base_image->mlx, data->base_image->win_ptr);
	mlx_destroy_display(data->base_image->mlx);
	free(data->base_image->mlx);
	free_data(data);
	exit(EXIT_SUCCESS);
}

int	esc_close_win(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
		destroy_window(data);
	return (SUCCESS);
}

int	cross_close_win(t_data *data)
{
	destroy_window(data);
	return (SUCCESS);
}
