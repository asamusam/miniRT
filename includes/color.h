/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:17:17 by asamuilk          #+#    #+#             */
/*   Updated: 2024/05/03 13:38:24 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	float	transparent;
	float	red;
	float	green;
	float	blue;
}	t_color;

void	print_color(t_color *color);
t_color	color(float transparent, float red, float green, float blue);
int		create_trgb(int t, int r, int g, int b);

#endif