/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:21:25 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/01 14:36:35 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "tuples.h"
# include "color.h"

typedef struct s_ambient
{
	float		intensity;
	t_color		color;
}	t_ambient;

typedef struct s_light
{
	t_tuple		position;
	float		intensity;
	t_color		color;
}	t_light;

#endif