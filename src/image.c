/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:02:51 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 18:25:31 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		new_x;
	int		new_y;

	if (color == (int)0xFF000000)
		return ;
	new_x = (WIDTH / 2) + x;
	new_y = (HEIGHT / 2) - y;
	dst = img->addr + (new_y * img->line_len + new_x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
