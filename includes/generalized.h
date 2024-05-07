/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalized.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:32:17 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/07 17:54:57 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERALIZED_H
# define GENERALIZED_H

typedef enum e_object_type
{
	PLANE,
	SPHERE,
	CYLINDER
}	t_object_type;

typedef struct s_object
{
	int		type;
	void	*object;
}	t_object;

void	init_objects(t_data *data);
t_list	*shape_intersect(t_object *obj, t_ray ray);

#endif