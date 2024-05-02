/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:58:30 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/02 15:49:05 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_H
# define TUPLES_H

typedef enum e_tuple_type
{
	VECTOR = 0,
	POINT = 1
}	t_tuple_type;

typedef struct s_tuple
{
	float			x;
	float			y;
	float			z;
	t_tuple_type	w;
}	t_tuple;

#endif