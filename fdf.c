/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:22:06 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/15 20:15:46 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_params	params;
	t_point		start;
	double		angles[2];

	angles[0] = M_PI / 4;
	angles[1] = 0.03 * M_PI;
	initialize_params(&params);
	if (argc != 2)
		clean_exit(&params, "Usage: ./fdf <filename>", 0);
	check_file_extension(&params, argv[1]);
	check_map(&params, argv[1]);
	get_map(&params, argv[1]);
	params.map_scale = round(1060 * 0.707 / params.map_cols);
	start.color = create_trgb(0, 255, 255, 0);
	start.x = 700;
	start.y = 300;
	plain_map(&params, start, params.map_scale);
	rotate_2d(&params, start, M_PI / 4);
	iso_proj(&params, start, angles);
	init_window(&params, argv[1]);
	draw_map(&params);
	mlx_put_image_to_window(params.mlx, params.win, params.img, 0, 0);
	mlx_loop(params.mlx);
	clean_exit(&params, NULL, 0);
}

void	clean_exit(t_params *params, char *msg, int error)
{
	if (error != 0)
		perror(msg);
	else if (msg != NULL)
		ft_putendl_fd(msg, 1);
	clean_params(params);
	exit(error);
}

void	initialize_params(t_params *params)
{
	params->mlx = NULL;
	params->win = NULL;
	params->img = NULL;
	params->addr = NULL;
	params->bits_per_pixel = 0;
	params->line_length = 0;
	params->endian = 0;
	params->fd = -1;
	params->map_lines = 0;
	params->map_cols = 0;
	params->map_scale = 0;
	params->map_3d = NULL;
	params->map_2d = NULL;
}

void	clean_params(t_params *params)
{
	if (params->fd != -1)
	{
		close(params->fd);
		params->fd = -1;
	}
	if (params->map_3d != NULL)
	{
		free_matrix((void **) params->map_3d);
		params->map_3d = NULL;
	}
	if (params->map_2d != NULL)
	{
		free_matrix((void **) params->map_2d);
		params->map_2d = NULL;
	}
}

void	check_file_extension(t_params *params, char *file_path)
{
	char	*extension;
	size_t	len;

	len = 4;
	extension = ft_strrchr(file_path, '.');
	if (!extension)
		clean_exit(params, "Wrong file extension. Expected: .fdf", 0);
	if (ft_strlen(extension) > len)
		len = ft_strlen(extension);
	if (ft_strncmp(extension, ".fdf", len))
		clean_exit(params, "Wrong file extension. Expected: .fdf", 0);
}
