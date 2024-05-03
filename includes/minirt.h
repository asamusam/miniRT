/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/05/03 13:36:12 by asamuilk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include "scene.h"

# define HEIGHT 1080
# define WIDTH 1080
# define BG_COLOR 0x000000
# define FAIL 1
# define SUCCESS 0

typedef enum e_keycode
{
	ESC_KEY = 0xff1b,
}	t_keycode;

typedef struct s_img
{
	void	*mlx;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_data
{
	t_img	*base_image;
	t_scene	*scene;
}	t_data;

// init.c

void	allocate_data(t_data **data);
void	init_mlx(t_data *data);
void	init_data(t_data *data);

// image.c

void	put_pixel_img(t_img *img, int x, int y, int color);

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
