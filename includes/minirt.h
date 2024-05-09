/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:49:48 by llai              #+#    #+#             */
/*   Updated: 2024/05/08 21:38:01 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>

# define HEIGHT 400 
# define WIDTH 400
# define BG_COLOR 0x000000
# define FAIL 1
# define SUCCESS 0

typedef struct s_img	t_img;
typedef struct s_scene	t_scene;

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
