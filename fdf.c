/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 19:22:06 by bcastelo          #+#    #+#             */
/*   Updated: 2023/07/09 12:10:05 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_close_window(int keycode, t_vars *vars)
{
	ft_printf("Key pressed: %i - %#x\n", keycode, keycode);
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
	}
	return (0);
}

int	get_button_and_coord(t_vars *vars)
{
	(void) vars;
	ft_printf("Window closed\n");
	exit(0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, 2, 1L << 0, key_close_window, &vars);
	mlx_hook(vars.win, 17, 0, get_button_and_coord, &vars);
	mlx_loop(vars.mlx);
	exit(0);
}
