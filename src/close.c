/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:03 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 20:50:43 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdlib.h>

void	free_object_matrix(void *content)
{
	t_sphere	*s;
	
	s = content;
	if (s->transform)
	{
		free_matrix(&s->transform);
	}
}

void	free_data(t_data *data)
{
	if (data->base_image)
		free(data->base_image);
	if (data->scene)
	{
		if (data->scene->spheres)
		{
			ft_lstiter(data->scene->spheres, free_object_matrix);
			ft_lstclear(&data->scene->spheres, free);
		}
		if (data->scene->cylinders)
			ft_lstclear(&data->scene->cylinders, free);
		if (data->scene->planes)
			ft_lstclear(&data->scene->planes, free);
		if (data->scene->camera.transform)
		{
			free_matrix(&data->scene->camera.transform);
			data->scene->camera.transform = NULL;
		}
		if (data->scene->world.objects)
		{
			free(data->scene->world.objects);
			// ft_lstiter(data->scene->world.objects, free_object_matrix);
			// ft_lstclear(&data->scene->world.objects, free);
		}
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
