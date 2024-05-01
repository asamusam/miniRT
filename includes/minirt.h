/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 14:50:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "image.h"
# include "shapes.h"
# include "matrix.h"
# include <math.h>

// # define ESC_KEY 0xff1b
# define HEIGHT 1080
# define WIDTH 1080
# define BG_COLOR 0x000000

// typedef struct s_vec3 t_vec3;
typedef enum e_keycode
{
	ESC_KEY = 0xff1b,
}	t_keycode;

typedef struct s_data
{
	t_img	base_image;
}	t_data;

t_win	new_window(int w, int h, char *str);

// Render.c
void	render(t_data *data);
void	clear_image(t_data *data);

// control.c
int	key_down(int keycode, t_data *data);

// close.c
int		destroy_window(t_data *data);
int		esc_close_win(int keycode, t_data *data);
int		cross_close_win(t_data *data);

#endif // !MINIRT_H
