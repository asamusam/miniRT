/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:35:30 by llai              #+#    #+#             */
/*   Updated: 2024/05/02 15:58:21 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "color.h"

typedef struct s_win
{
	void	*mlx;
	void	*win_ptr;
	int		width;
	int		height;
}	t_win;

typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

void	put_pixel(t_img img, int x, int y, t_color color);
void	put_pixel2(t_img img, int x, int y, t_color color);
void	put_pixel_img(t_img img, int x, int y, int color);
t_img	new_img(int width, int height, t_win window);

#endif // !IMAGE_H
