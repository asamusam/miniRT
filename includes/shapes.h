/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:02:29 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/01 14:41:56 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include "tuples.h"
# include "color.h"

typedef struct s_sphere
{
	t_tuple		center;
	float		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_cylinder
{
	t_tuple		center;
	t_tuple		axis;
	float		diameter;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_plane
{
	t_tuple		point;
	t_tuple		normal;
	t_color		color;
}	t_plane;

#endif