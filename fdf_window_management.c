/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_window_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:03:43 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/14 21:25:58 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_window(t_params *params, char *title)
{
	params->mlx = mlx_init();
	params->win = mlx_new_window(params->mlx, 1920, 1080, title);
	params->img = mlx_new_image(params->mlx, 1920, 1080);
	params->addr = mlx_get_data_addr(params->img, &params->bits_per_pixel,
			&params->line_length, &params->endian);
	mlx_hook(params->win, 2, 1L << 0, key_close_window, params);
	mlx_hook(params->win, 17, 0, window_destroy_handler, params);
	mlx_hook(params->win, 12, 1L << 15, refresh_window, params);
}

int	key_close_window(int keycode, t_params *params)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_image(params->mlx, params->img);
		mlx_destroy_window(params->mlx, params->win);
		mlx_destroy_display(params->mlx);
		free(params->mlx);
		clean_exit(params, NULL, 0);
	}
	return (0);
}

int	window_destroy_handler(t_params *params)
{
	mlx_destroy_image(params->mlx, params->img);
	mlx_destroy_window(params->mlx, params->win);
	mlx_destroy_display(params->mlx);
	free(params->mlx);
	clean_exit(params, NULL, 0);
	return (1);
}

int	refresh_window(t_params *params)
{
	if (params->img == NULL)
		return (0);
	mlx_put_image_to_window(params->mlx, params->win, params->img, 0, 0);
	return (0);
}
