/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:05:03 by llai              #+#    #+#             */
/*   Updated: 2024/05/13 17:20:08 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/shapes.h"
#include "../includes/matrix.h"
#include "../includes/scene.h"
#include "../includes/image.h"

void	free_object(void *content)
{
	t_object	*object;

	object = (t_object *)content;
	free(object->object);
	free(object);
}

void	free_data(t_data *data)
{
	if (data->base_image)
		free(data->base_image);
	if (data->scene)
	{
		if (data->scene->world.objects)
			ft_lstclear(&data->scene->world.objects, free_object);
		if (data->scene->cylinders)
			ft_lstclear(&data->scene->cylinders, free);
		free(data->scene);
	}
	free(data);
}

void	print_sphere_list(t_list *lst)
{
	t_sphere	*s;

	while (lst)
	{
		s = lst->content;
		print_tuple2(s->center);
		lst = lst -> next;
	}
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
