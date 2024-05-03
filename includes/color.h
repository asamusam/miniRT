/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:22:50 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 17:11:16 by llai             ###   ########.fr       */
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

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
t_color	color(float transparent, float red, float green, float blue);
int		create_trgb_color(float t, float r, float g, float b);
t_color	add_colors(t_color c1, t_color c2);
t_color	sub_colors(t_color c1, t_color c2);
t_color	mul_color(t_color c, float scalar);
t_color	hadamard_product(t_color c1, t_color c2);
void	print_color(t_color color);

#endif // !COLOR_H
