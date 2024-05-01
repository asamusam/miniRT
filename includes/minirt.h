/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asamuilk <asamuilk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/05/01 20:11:38 by asamuilk         ###   ########.fr       */
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

typedef enum e_keycode
{
	ESC_KEY = 0xff1b,
}	t_keycode;

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

typedef struct s_data
{
	t_img	base_image;
	t_scene	scene;
}	t_data;

// init.c

t_win	new_window(int w, int h, char *str);
void	init_data(t_data *data);

// color.c

int		create_trgb(int t, int r, int g, int b);
t_color	color(double transparent, double red, double green, double blue);

// image.c

void	put_pixel(t_img img, int x, int y, int color);
void	put_pixel_img(t_img img, int x, int y, int color);
t_img	new_img(int width, int height, t_win window);

// close.c

void	free_scene(t_data *data);
int		destroy_window(t_data *data);
int		esc_close_win(int keycode, t_data *data);
int		cross_close_win(t_data *data);

// parse.c

int		parse(t_data *data, char *scene_file);

// color.c

t_color	color(double transparent, double red, double green, double blue);

// ft_atof.c

int		ft_isspace(int c);
double	ft_atof(const char *str);

#endif // !MINIRT_H
