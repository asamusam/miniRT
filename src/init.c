/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:58 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 21:57:51 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/image.h"
#include "../includes/scene.h"

void	allocate_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		perror("minirt: allocate_data:");
		exit(EXIT_FAILURE);
	}
}

void	init_mlx(t_data *data)
{
	t_img	*img;

	data->base_image = malloc(sizeof(t_img));
	img = data->base_image;
	if (!img)
	{
		perror("minirt: init_mlx:");
		free_data(data);
		exit(EXIT_FAILURE);
	}
	img->mlx = mlx_init();
	img->win_ptr = mlx_new_window(img->mlx, WIDTH, HEIGHT, "miniRT");
	img->img_ptr = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, \
								&img->line_len, &img->endian);
	mlx_hook(img->win_ptr, 2, 1L << 0, esc_close_win, data);
	mlx_hook(img->win_ptr, 17, 0, cross_close_win, data);
}

void	init_data(t_data *data)
{
	data->scene = malloc(sizeof(t_scene));
	if (!data->scene)
	{
		perror("minirt: init_data:");
		free(data);
		exit(EXIT_FAILURE);
	}
	data->scene->ambient.color = color(0, 0, 0, 0);
	data->scene->ambient.intensity = 0.0;
	data->scene->camera.fov = 0;
	data->scene->camera.position = (t_tuple){0, 0, 0, POINT};
	data->scene->camera.rotation = (t_tuple){0, 0, 0, VECTOR};
	data->scene->light.color = color(0, 0, 0, 0);
	data->scene->light.intensity = 0.0;
	data->scene->light.position = (t_tuple){0, 0, 0, POINT};
	data->scene->cylinders = NULL;
	data->scene->planes = NULL;
	data->scene->spheres = NULL;
	data->scene->world.objects = NULL;
	data->base_image = NULL;
}
