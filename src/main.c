/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/09 16:44:18 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include "../includes/world.h"
#include "../includes/scene.h"
#include "../includes/image.h"

void	sphere_scene(t_data *data)
{
	render(data, data->scene->camera, data->scene->world);
	printf("\ndone\n");
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 2)
	{
		allocate_data(&data);
		init_data(data);
		parse(data, av[1]);
		init_world(data);
		// print_scene(data);
		init_mlx(data);
		printf("render\n");
		sphere_scene(data);
		mlx_loop(data->base_image->mlx);
	}
}
