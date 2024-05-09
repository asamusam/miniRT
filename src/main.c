/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:43:24 by llai              #+#    #+#             */
/*   Updated: 2024/05/09 23:03:57 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minirt.h"
#include "../includes/world.h"
#include "../includes/scene.h"
#include "../includes/image.h"
#include "../includes/matrix.h"

t_sphere	sphere(t_tuple center, float radius)
{
	t_sphere	s;

	s.center = center;
	s.radius = radius;
	s.transform = init_identitymatrix(4);
	s.material = material();
	return (s);
}
t_world	world(void)
{
	t_world	world;

	world.objects = NULL;
	world.light = point_light(point(0, 0, 0), 1, color(0, 1, 1, 1));
	return (world);
}
t_world	default_world(void)
{
	t_world	new_world;
	t_sphere	*s1;
	t_sphere	*s2;

	new_world = world();
	new_world.objects = NULL;
	s1 = malloc_sphere();
	s1->material.color = color(0, 0.8, 1, 0.6);
	s1->material.diffuse = 0.7;
	s1->material.specular = 0.2;
	s1->transform = init_identitymatrix(4);
	s2 = malloc_sphere();
	s2->transform = scaling(0.5, 0.5, 0.5);
	ft_lstadd_back(&new_world.objects, ft_lstnew(s1));
	ft_lstadd_back(&new_world.objects, ft_lstnew(s2));
	new_world.light = point_light(point(0, 0, -10), 1, color(0, 1, 1, 1));
	return (new_world);
}

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
		// t_world w = default_world();
		// int	i = is_shadowed(w, point(-2, 2, -2));
		printf("render\n");
		sphere_scene(data);
		mlx_loop(data->base_image->mlx);
	}
}
