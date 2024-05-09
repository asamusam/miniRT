/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:10:35 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/08 22:01:32 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include "../includes/tuples.h"
#include "../includes/shapes.h"
#include "../includes/scene.h"

void	print_tuple(t_tuple *tuple)
{
	if (tuple->w == POINT)
		printf("point x - %f, y - %f, z - %f)", tuple->x, tuple->y, tuple->z);
	else
		printf("vector x - %f, y - %f, z - %f)", tuple->x, tuple->y, tuple->z);
}

void	print_sphere(void *sp)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)sp;
	printf("Sphere\n-----\nPosition: ");
	print_tuple(&sphere->center);
	printf("\nDiameter: %f\nColor: ", sphere->diameter);
	print_color(&sphere->color);
	printf("\n-----\n");
}

void	print_plane(void *pl)
{
	t_plane	*plane;

	plane = (t_plane *)pl;
	printf("Plane\n-----\nPosition: ");
	print_tuple(&plane->point);
	printf("\nNormal: ");
	print_tuple(&plane->normal);
	printf("\nColor: ");
	print_color(&plane->color);
	printf("\n-----\n");
}

void	print_cylinder(void *cy)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)cy;
	printf("Cylinder\n-----\nPosition: ");
	print_tuple(&cylinder->center);
	printf("\nAxis: ");
	print_tuple(&cylinder->axis);
	printf("\nDiameter: %f\nHeight: %f\nColor: ", \
			cylinder->diameter, cylinder->height);
	print_color(&cylinder->color);
	printf("\n-----\n");
}

void	print_scene(t_data *data)
{
	printf("Ambient\n-----\nIntensity: %f\nColor: ", \
			data->scene->ambient.intensity);
	print_color(&data->scene->ambient.color);
	printf("\n-----\n");
	printf("Camera\n-----\nPosition: ");
	print_tuple(&data->scene->camera.position);
	printf("\nRotation: ");
	print_tuple(&data->scene->camera.rotation);
	printf("\nFOV: %f\n-----\n", data->scene->camera.fov);
	printf("Light\n-----\nPosition: ");
	print_tuple(&data->scene->light.position);
	printf("\nIntensity: %f\nColor: ", data->scene->light.intensity);
	print_color(&data->scene->light.color);
	printf("\n-----\n");
	ft_lstiter(data->scene->spheres, print_sphere);
	ft_lstiter(data->scene->planes, print_plane);
	ft_lstiter(data->scene->cylinders, print_cylinder);
}
