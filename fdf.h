/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:51:35 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 19:32:28 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <mlx.h>

# define ESC_KEY 65307
# define MAX_WIDTH 1920
# define MAX_HEIGHT 1080

typedef struct s_point {
	int		x;
	int		y;
	int		color;
}				t_point;

typedef struct s_point_3d {
	int		x;
	int		y;
	int		z;
}				t_point_3d;

typedef struct s_params {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		fd;
	int		map_lines;
	int		map_cols;
	int		map_scale;
	int		**map_3d;
	t_point	**map_2d;
}				t_params;

void			init_window(t_params *params, char *title);

int				key_close_window(int keycode, t_params *params);

int				window_destroy_handler(t_params *params);

int				refresh_window(t_params *params);

void			clean_exit(t_params *params, char *msg, int error);

void			initialize_params(t_params *params);

void			clean_params(t_params *params);

void			check_file_extension(t_params *params, char *file_path);

void			check_map(t_params *params, char *file_path);

void			get_map(t_params *params, char *file_path);

void			init_2d_map(t_params *params);

void			free_matrix(void **matrix);

void			print_map_3d(t_params *params);

void			plain_map(t_params *params, t_point start, int scale);

void			rotate_2d(t_params *params, t_point start, double angle);

void			iso_proj(t_params *params, t_point start, double angles[2]);

int				create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);

unsigned char	get_t(int trgb);

unsigned char	get_r(int trgb);

unsigned char	get_g(int trgb);

unsigned char	get_b(int trgb);

void			draw_point(t_params *params, int x, int y, int color);

/* Using Bresenham's line algorithm */
void			draw_line(t_params *params, t_point start, t_point end);

void			draw_map(t_params *params);

#endif