/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/05/07 14:33:37 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "image.h"
# include "shapes.h"
# include "matrix.h"
# include "world.h"
# include "scene.h"
# include "parser.h"
# include "color.h"
# include <math.h>

// # define ESC_KEY 0xff1b
# define HEIGHT 400 
# define WIDTH 400
# define BG_COLOR 0x000000
# define FAIL 1
# define SUCCESS 0

// typedef struct s_vec3 t_vec3;
typedef enum e_keycode
{
	ESC_KEY = 0xff1b,
}	t_keycode;

typedef struct s_data
{
	t_img	*base_image;
	t_scene	*scene;
}	t_data;

// init.c

void	allocate_data(t_data **data);
void	init_mlx(t_data *data);
void	init_data(t_data *data);

// Render.c
// void	render(t_data *data);
void	clear_image(t_data *data);

// control.c
int		key_down(int keycode, t_data *data);
// image.c

// void	put_pixel_img(t_img *img, int x, int y, int color);

// close.c

void	free_data(t_data *data);
int		destroy_window(t_data *data);
int		esc_close_win(int keycode, t_data *data);
int		cross_close_win(t_data *data);

// parse.c

void	parse(t_data *data, char *scene_file);

// print.c

void	print_scene(t_data *data);

#endif // !MINIRT_H
